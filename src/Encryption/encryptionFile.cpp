#include "encryption.h"
#include <chrono>

std::vector<siteObj> siteDataNew;

encryption::encryption(){

}

void encryption::encrypt(){    
    encryptVectorToFile(pathS, convertToRawString(siteDataNew), fetchHash());
}

void encryption::decrypt(){
    decryptContentToRAM(pathS, rawStr, fetchHash());
}

bool encryption::isPasswordCorrect(const std::string& password, const std::string& storedHash) {
    if (crypto_pwhash_str_verify(storedHash.c_str(), password.c_str(), password.length()) == 0) {
        return true; // Password matches
    }    
    return false; // Wrong password or corrupted hash
}

std::string encryption::hashPassword(const std::string& password) {
    char hashed_password[crypto_pwhash_STRBYTES];

    // crypto_pwhash_str handles salt generation automatically
    if (crypto_pwhash_str(hashed_password, password.c_str(), password.length(),
            customOpsLimit, // Moderate CPU usage
            customMemLimit  // Moderate RAM usage
        ) != 0) {
        return "\nOut of memory or system error during hashing\n";
    }
    return std::string(hashed_password);
}

std::vector<uint8_t> encryption::serializeVector(const std::vector<std::string>& vec) {
    // 1. Calculate total size upfront
    size_t totalSize = 0;
    for (const auto& str : vec) {
        totalSize += sizeof(uint64_t) + str.size();
    }

    // 2. Pre-allocate memory once
    std::vector<uint8_t> buffer;
    buffer.reserve(totalSize); 

    // 3. Populate buffer
    for (const auto& str : vec) {
        uint64_t len = str.size();
        const uint8_t* lenBytes = reinterpret_cast<const uint8_t*>(&len);
        buffer.insert(buffer.end(), lenBytes, lenBytes + sizeof(len));
        buffer.insert(buffer.end(), str.begin(), str.end());
    }
    return buffer;
}


bool encryption::encryptVectorToFile(const filesystem::path& targetPath, const std::vector<std::string>& dataVector, const std::string& password) {

    // Harden Key Derivation Limits for a Password Manager
    unsigned char salt[crypto_pwhash_SALTBYTES];
    randombytes_buf(salt, sizeof salt);

    unsigned char key[crypto_secretstream_xchacha20poly1305_KEYBYTES];


    // Using MODERATE limits
    if (crypto_pwhash(key, sizeof key, password.c_str(), password.length(), salt,
                    customOpsLimit,
                    customMemLimit,
                    crypto_pwhash_ALG_ARGON2ID13) != 0) {
        std::cerr << "Error: Key derivation failed (Out of memory).\n";
        return false;
    }

    // Serialize data to resolve the delimiter/continuous stream problem
    std::vector<uint8_t> serializedData = serializeVector(dataVector);

    // Prepare Temporary File Path for Atomic Saving
    filesystem::path tmpPath = targetPath;
    tmpPath.replace_extension(".tmp");

    // Open file stream explicitly in BINARY mode (No text extensions like .txt)
    std::ofstream outFile(tmpPath, std::ios::binary);
    if (!outFile) {
        std::cerr << "Error: Could not open temporary file for writing.\n";
        sodium_memzero(key, sizeof key);
        return false;
    }

    // Write salt to the file header so we can derive the key again during decryption
    outFile.write(reinterpret_cast<const char*>(salt), sizeof salt);

    // Initialize the Secretstream
    crypto_secretstream_xchacha20poly1305_state state;
    unsigned char header[crypto_secretstream_xchacha20poly1305_HEADERBYTES];
    crypto_secretstream_xchacha20poly1305_init_push(&state, header, key);
    
    // Securely wipe the raw key from RAM immediately after initializing the stream
    sodium_memzero(key, sizeof key);

    // Write stream header to file
    outFile.write(reinterpret_cast<const char*>(header), sizeof header);

    const size_t CHUNK_SIZE_EN = CHUNK_SIZE;
    unsigned char ciphertext[CHUNK_SIZE_EN + crypto_secretstream_xchacha20poly1305_ABYTES];
    unsigned long long cipherLen;
    
    size_t bytesProcessed = 0;
    while (bytesProcessed < serializedData.size()) {
        size_t bytesToRead = std::min(CHUNK_SIZE_EN, serializedData.size() - bytesProcessed);
        unsigned char tag = (bytesProcessed + bytesToRead == serializedData.size()) 
                            ? crypto_secretstream_xchacha20poly1305_TAG_FINAL 
                            : crypto_secretstream_xchacha20poly1305_TAG_MESSAGE;

        crypto_secretstream_xchacha20poly1305_push(&state, ciphertext, &cipherLen, 
                                                   &serializedData[bytesProcessed], bytesToRead, 
                                                   nullptr, 0, tag);
        
        outFile.write(reinterpret_cast<const char*>(ciphertext), cipherLen);
        bytesProcessed += bytesToRead;
    }

    outFile.close();

    // Perform Atomic Save: Rename/replace the original file safely using OS operations
    try {
        filesystem::rename(tmpPath, targetPath);
    } catch (const filesystem::filesystem_error& e) {
        std::cerr << "Error executing atomic rename: " << e.what() << "\n";
        filesystem::remove(tmpPath); // Clean up temp file
        return false;
    }

    return true;
}


std::vector<std::string> encryption::deserializeVector(const std::vector<uint8_t>& buffer) {
    std::vector<std::string> vec;
    size_t offset = 0;

    while (offset < buffer.size()) {
        // Ensure there are at least 8 bytes left to read the string length
        if (offset + sizeof(uint64_t) > buffer.size()) {
            std::cerr << "Warning: Corrupted serialization boundaries. Truncating.\n";
            break;
        }

        // Read length prefix
        uint64_t len;
        std::copy(buffer.begin() + offset, buffer.begin() + offset + sizeof(uint64_t), reinterpret_cast<uint8_t*>(&len));
        offset += sizeof(uint64_t);

        // Ensure the buffer actually contains the amount of bytes specified by length
        if (offset + len > buffer.size()) {
            std::cerr << "Warning: String length exceeds remaining buffer size. Truncating.\n";
            break;
        }

        // Extract string data
        std::string str(buffer.begin() + offset, buffer.begin() + offset + len);
        vec.push_back(str);
        offset += len;
    }
    return vec;
}

bool encryption::decryptContentToRAM(const filesystem::path& sourcePath, std::vector<std::string>& outVector, const std::string& password) {
    // Initialize libsodium
    if (sodium_init() < 0) {
        std::cerr << "Error: Libsodium initialization failed.\n";
        return false;
    }

    // Open file stream explicitly in BINARY mode
    std::ifstream inFile(sourcePath, std::ios::binary);
    if (!inFile) {
        std::cerr << "Error: Could not open encrypted file for reading.\n";
        return false;
    }

    // Read the Salt from the file header
    unsigned char salt[crypto_pwhash_SALTBYTES];
    inFile.read(reinterpret_cast<char*>(salt), sizeof salt);
    if (inFile.gcount() != sizeof salt) {
        std::cerr << "Error: Failed to read salt header.\n";
        return false;
    }

    // Derive the key using identical SENSITIVE boundaries used during encryption
    unsigned char key[crypto_secretstream_xchacha20poly1305_KEYBYTES];
    if (crypto_pwhash(key, sizeof key, password.c_str(), password.length(), salt,
                     customOpsLimit, 
                     customMemLimit,
                     crypto_pwhash_ALG_ARGON2ID13) != 0) {
        std::cerr << "Error: Key derivation failed (Out of memory).\n";
        return false;
    }

    // Read the Secretstream Header from the file
    unsigned char header[crypto_secretstream_xchacha20poly1305_HEADERBYTES];
    inFile.read(reinterpret_cast<char*>(header), sizeof header);
    if (inFile.gcount() != sizeof header) {
        std::cerr << "Error: Failed to read stream header.\n";
        sodium_memzero(key, sizeof key);
        return false;
    }

    // Initialize the Secretstream for pull/decryption
    crypto_secretstream_xchacha20poly1305_state state;
    if (crypto_secretstream_xchacha20poly1305_init_pull(&state, header, key) != 0) {
        std::cerr << "Error: Invalid stream header or corrupted file.\n";
        sodium_memzero(key, sizeof key);
        return false;
    }

    // Securely wipe the raw key from RAM immediately after initialization
    sodium_memzero(key, sizeof key);

    std::vector<uint8_t> decryptedBuffer;
    const size_t CHUNK_SIZE_DE = CHUNK_SIZE;
    // Ciphertext blocks include the authentication tag overhead (ABYTES)
    const size_t CIPHER_CHUNK_SIZE = CHUNK_SIZE_DE + crypto_secretstream_xchacha20poly1305_ABYTES;
    
    unsigned char ciphertext[CIPHER_CHUNK_SIZE];
    unsigned char decryptedChunk[CHUNK_SIZE_DE];
    unsigned long long decryptLen;
    unsigned char tag;

    // Process file data chunks
    while (inFile.read(reinterpret_cast<char*>(ciphertext), CIPHER_CHUNK_SIZE) || inFile.gcount() > 0) {
        size_t bytesRead = inFile.gcount();

        if (crypto_secretstream_xchacha20poly1305_pull(&state, decryptedChunk, &decryptLen, &tag,
                                                       ciphertext, bytesRead, nullptr, 0) != 0) {
            std::cerr << "Error: Decryption failed. Corrupted data or wrong password.\n";
            return false;
        }


        // Append the decrypted chunk bytes to our serialization buffer
        decryptedBuffer.insert(decryptedBuffer.end(), decryptedChunk, decryptedChunk + decryptLen);

        // Terminate successfully if the final tag marker is reached
        if (tag == crypto_secretstream_xchacha20poly1305_TAG_FINAL) {
            break;
        }
    }
    inFile.close();

    // Deserialize the raw sequential stream back into separate vector entries
    outVector = deserializeVector(decryptedBuffer);
    return true;
}
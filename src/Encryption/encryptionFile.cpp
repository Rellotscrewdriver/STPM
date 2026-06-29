#include "encryption.h"
#include <chrono>

std::vector<std::string> siteData;

encryption::encryption(){

}

//using the hash as key
void encryption::encrypt(){
    encryptFile(tempFileS, pathS, fetchHash());
    std::rename(tempFileS, pathS);
}

void encryption::decrypt(){
    decryptFile(tempFileS, pathS, fetchHash());
    std::rename(tempFileS, pathS);
}

void encryption::encryptRAM(){
    auto startTime = std::chrono::steady_clock::now();
    convertToRawString();
    encryptVectorToFile(pathS, rawStr, fetchHash());
    auto endTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    std::cout << "[BENCHMARK] Encryption took: " << duration << " ms (" 
              << (duration / 1000.0) << " seconds)\n";

    std::cout << "EncryptionRAM\n";
    for(auto &i : siteDataNew){
      std::cout << "Data: " << i.getEmail() << " " << i.getLink() << " " << i.getPass() << "\n";
    }
}

void encryption::decryptRAM(){
    auto startTime = std::chrono::steady_clock::now();
    decryptContentToRAM(pathS, rawStr, fetchHash());
    auto endTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    std::cout << "[BENCHMARK] Decryption took: " << duration << " ms (" 
              << (duration / 1000.0) << " seconds)\n";

    convertToVectObj();
    std::cout << "DecryptionRAM\n";
    for(auto &i : siteDataNew){
      std::cout << "Data: " << i.getEmail() << " " << i.getLink() << " " << i.getPass() << "\n";
    }
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
            crypto_pwhash_OPSLIMIT_MODERATE, // Moderate CPU usage
            crypto_pwhash_MEMLIMIT_MODERATE  // Moderate RAM usage
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
    // std::vector<uint8_t> buffer;
    // for (const auto& str : vec) {
    //     uint64_t len = str.size();
    //     // Append length (8 bytes)
    //     const uint8_t* lenBytes = reinterpret_cast<const uint8_t*>(&len);
    //     buffer.insert(buffer.end(), lenBytes, lenBytes + sizeof(len));
    //     // Append string data
    //     buffer.insert(buffer.end(), str.begin(), str.end());
    // }
    // return buffer;
}


bool encryption::encryptVectorToFile(const filesystem::path& targetPath, const std::vector<std::string>& dataVector, const std::string& password) {

    // Harden Key Derivation Limits for a Password Manager
    unsigned char salt[crypto_pwhash_SALTBYTES];
    randombytes_buf(salt, sizeof salt);

    unsigned char key[crypto_secretstream_xchacha20poly1305_KEYBYTES];


    // Using SENSITIVE limits to dramatically increase offline brute-force cost
    if (crypto_pwhash(key, sizeof key, password.c_str(), password.length(), salt,
                     crypto_pwhash_OPSLIMIT_MODERATE, 
                     crypto_pwhash_MEMLIMIT_MODERATE,
                     crypto_pwhash_ALG_DEFAULT) != 0) {
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
        std::cout << "Infinite loop?\n";
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
                     crypto_pwhash_OPSLIMIT_MODERATE, 
                     crypto_pwhash_MEMLIMIT_MODERATE, 
                     crypto_pwhash_ALG_DEFAULT) != 0) {
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

bool encryption::encryptFile(const char* target_file, const char* source_file, const std::string& password) {
    std::ifstream fp_t(source_file, std::ios::binary | std::ios::app);
    std::ofstream fp_e(target_file, std::ios::binary | std::ios::app);
    if (!fp_t.is_open() || !fp_e.is_open()) return false;

    // generate a random salt
    unsigned char salt[crypto_pwhash_SALTBYTES];
    randombytes_buf(salt, sizeof salt);

    // derive the key from the password and salt
    unsigned char key[crypto_secretstream_xchacha20poly1305_KEYBYTES];
    if (crypto_pwhash(key, sizeof key, password.c_str(), password.length(), salt,
                      crypto_pwhash_OPSLIMIT_INTERACTIVE, crypto_pwhash_MEMLIMIT_INTERACTIVE,
                      crypto_pwhash_ALG_DEFAULT) != 0) {
        return false; // Out of memory
    }

    crypto_secretstream_xchacha20poly1305_state st;
    unsigned char header[crypto_secretstream_xchacha20poly1305_HEADERBYTES];

    crypto_secretstream_xchacha20poly1305_init_push(&st, header, key);

    // Anyone can see this, but they can't decrypt without the password
    fp_e.write(reinterpret_cast<char*>(salt), sizeof(salt));
    fp_e.write(reinterpret_cast<char*>(header), sizeof(header));

    std::vector<unsigned char> in_buf(CHUNK_SIZE);
    std::vector<unsigned char> out_buf(CHUNK_SIZE + crypto_secretstream_xchacha20poly1305_ABYTES); 
    unsigned long long out_len;
    bool eof = false;

    while (!eof) {
        fp_t.read(reinterpret_cast<char*>(in_buf.data()), CHUNK_SIZE);
        std::streamsize read_bytes = fp_t.gcount();
        eof = fp_t.eof();
        unsigned char tag = eof ? crypto_secretstream_xchacha20poly1305_TAG_FINAL : 0;

        crypto_secretstream_xchacha20poly1305_push(&st, out_buf.data(), &out_len, in_buf.data(), read_bytes, NULL, 0, tag);
        fp_e.write(reinterpret_cast<char*>(out_buf.data()), out_len);
    }

    // Clear the key from memory immediately for security
    sodium_memzero(key, sizeof key); 
    return true;
}

bool encryption::decryptFile(const char* target_file, const char* source_file, const std::string& password) {
    std::ifstream fp_e(source_file, std::ios::binary | std::ios::app);
    std::ofstream fp_t(target_file, std::ios::binary);
    if (!fp_e.is_open()) return false;

    unsigned char salt[crypto_pwhash_SALTBYTES];
    unsigned char header[crypto_secretstream_xchacha20poly1305_HEADERBYTES];

    //Read the Salt + Header stored in the file
    fp_e.read(reinterpret_cast<char*>(salt), sizeof(salt));
    fp_e.read(reinterpret_cast<char*>(header), sizeof(header));

    //Re-derive the exact same key using the file's salt and the user's password
    unsigned char key[crypto_secretstream_xchacha20poly1305_KEYBYTES];
    if (crypto_pwhash(key, sizeof key, password.c_str(), password.length(), salt,
                      crypto_pwhash_OPSLIMIT_INTERACTIVE, //moderate CPU usage 
                      crypto_pwhash_MEMLIMIT_INTERACTIVE, //limit RAM usage
                      crypto_pwhash_ALG_DEFAULT) != 0) {
        return false; // Out of memory
    }

    // Initialize decryption
    crypto_secretstream_xchacha20poly1305_state st;
    if (crypto_secretstream_xchacha20poly1305_init_pull(&st, header, key) != 0) {
        std::cerr << "Invalid header or wrong password!" << std::endl;
        sodium_memzero(key, sizeof key);
        return false;
    }

    std::vector<unsigned char> in_buf(CHUNK_SIZE + crypto_secretstream_xchacha20poly1305_ABYTES);
    std::vector<unsigned char> out_buf(CHUNK_SIZE);
    unsigned long long out_len;
    unsigned char tag;
    bool eof = false;

    while (!eof) {
        fp_e.read(reinterpret_cast<char*>(in_buf.data()), in_buf.size());
        std::streamsize read_bytes = fp_e.gcount();
        eof = fp_e.eof();
        if (read_bytes == 0) break;

        if (crypto_secretstream_xchacha20poly1305_pull(&st, out_buf.data(), &out_len, &tag, in_buf.data(), read_bytes, NULL, 0) != 0) {
            std::cerr << "Wrong password or file corrupted." << std::endl;
            sodium_memzero(key, sizeof key);
            return false;
        }
        fp_t.write(reinterpret_cast<char*>(out_buf.data()), out_len);
    }

    // Clear the key from memory
    sodium_memzero(key, sizeof key);
    fp_e.close();
    fp_t.close();

    return true;
}

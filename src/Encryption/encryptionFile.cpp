#include "encryption.h"

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
    encryptVectorToFile(pathS, fetchHash());
}


void encryption::decryptRAM(){
    decryptContentToRAM(pathS, pathS, fetchHash());
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
            crypto_pwhash_OPSLIMIT_INTERACTIVE, // Moderate CPU usage
            crypto_pwhash_MEMLIMIT_INTERACTIVE  // Moderate RAM usage
        ) != 0) {
        return "\nOut of memory or system error during hashing\n";
    }
    return std::string(hashed_password);
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

bool encryption::encryptVectorToFile(const char* target_file, const std::string& password) {
    // Open target file in binary mode
    std::ofstream fp_e(target_file, std::ios::binary);
    if (!fp_e.is_open()) return false;

    // Initialize sodium if not already done
    if (sodium_init() < 0) return false;

    // 1. Generate a random salt
    unsigned char salt[crypto_pwhash_SALTBYTES];
    randombytes_buf(salt, sizeof salt);

    // 2. Derive the key from the password and salt
    unsigned char key[crypto_secretstream_xchacha20poly1305_KEYBYTES];
    if (crypto_pwhash(key, sizeof key, password.c_str(), password.length(), salt,
                      crypto_pwhash_OPSLIMIT_INTERACTIVE, crypto_pwhash_MEMLIMIT_INTERACTIVE,
                      crypto_pwhash_ALG_DEFAULT) != 0) {
        return false; // Out of memory
    }

    // 3. Initialize the stream
    crypto_secretstream_xchacha20poly1305_state st;
    unsigned char header[crypto_secretstream_xchacha20poly1305_HEADERBYTES];
    crypto_secretstream_xchacha20poly1305_init_push(&st, header, key);

    // 4. Write salt and header to the file
    fp_e.write(reinterpret_cast<char*>(salt), sizeof(salt));
    fp_e.write(reinterpret_cast<char*>(header), sizeof(header));

    // 5. Buffer setup
    // Output buffer needs to accommodate the extra authentication tag overhead
    std::vector<unsigned char> out_buf(CHUNK_SIZE + crypto_secretstream_xchacha20poly1305_ABYTES); 
    unsigned long long out_len;

    // 6. Iterate through the vector and encrypt
    for (size_t i = 0; i < siteData.size(); ++i) {
        const std::string& current_str = siteData[i];
        size_t bytes_processed = 0;
        bool is_last_element = (i == siteData.size() - 1);

        // A string might be larger than CHUNK_SIZE, so chunk it if necessary
        do {
            size_t bytes_to_read = std::min(static_cast<size_t>(CHUNK_SIZE), current_str.length() - bytes_processed);
            const unsigned char* chunk_ptr = reinterpret_cast<const unsigned char*>(current_str.data() + bytes_processed);
            bytes_processed += bytes_to_read;

            // Define the tag: FINAL only if we are at the end of the final string
            bool is_end_of_stream = (is_last_element && bytes_processed >= current_str.length());
            unsigned char tag = is_end_of_stream ? crypto_secretstream_xchacha20poly1305_TAG_FINAL : 0;

            // Encrypt the chunk
            crypto_secretstream_xchacha20poly1305_push(
                &st, out_buf.data(), &out_len, 
                chunk_ptr, bytes_to_read, 
                NULL, 0, tag
            );

            // Write encrypted chunk to file
            fp_e.write(reinterpret_cast<char*>(out_buf.data()), out_len);

        } while (bytes_processed < current_str.length());
    }

    // 7. Clean up memory securely
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

bool encryption::decryptContentToRAM(const char* target_file, const char* source_file, const std::string& password) {
    std::ifstream fp_e(source_file, std::ios::binary | std::ios::app);
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
    std::vector<std::string> out_lines;
    std::string line_accumulator = "";
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

        for (unsigned long long i = 0; i < out_len; ++i) {
            char ch = static_cast<char>(out_buf[i]);
            if (ch == '\n') {
                out_lines.push_back(line_accumulator);
                line_accumulator.clear();
            } else if (ch != '\r') { // Ignore carriage returns for cross-platform safety
                line_accumulator.push_back(ch);
            }
        }
    }

    if (!line_accumulator.empty()) {
        out_lines.push_back(line_accumulator);
    }

    for(const auto &i : out_lines){
        std::cout << "Data: " << i << "\n";
    }

    // Clear the key from memory
    sodium_memzero(key, sizeof key);
    fp_e.close();

    return true;
}
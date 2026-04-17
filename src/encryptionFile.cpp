#include "encryption.h"

encryption::encryption(){

}

bool encryption::firstTimeUser(){
  namespace fs = std::filesystem;
  if (!fs::exists(path) || fs::is_empty(path)) {
    std::cout << "file is empty, creating it" << std::endl;
    createPassword();
    //create an empty file
    std::ofstream outFile(path);
    outFile.close();
    encrypt();
    return true; //means the user is new
  } else {
    if(verifyUser()){
        //std::cout << "Access Granted! Decrypting now";
        decrypt();
    }
  }
    return false; //means the user is old and grumpy
}

void encryption::createPassword(){
    std::string localPass;
    std::string localPass2;
    std::cout << "Welcome User! Please put a strong master password!\n";
    std::cout << "and make sure to remember it! you won't be able to retrive the sites if the master password is lost!\n";
    std::cout << "Password: ";
    std::getline(std::cin, localPass);
    std::cout << "enter the master password again!\n";
    std::cout << "Password: ";
    std::getline(std::cin, localPass2);

    if(localPass == localPass2){
        genHashtoFile(localPass);
    }
}

void encryption::genHashtoFile(std::string hashpass){
    std::ofstream password(passFile);
    password << hashPassword(hashpass);
    password.close();
};

std::string encryption::fetchHash(){
    std::ifstream password(passFile, std::ios::binary);    
    std::string temp;
    if(std::getline(password, temp)){
        password.close();
        return temp; //retrives the hash
    }
    return "FUCK YOU!! Stupid piece of shit";
}

bool encryption::verifyUser(){
    std::string password;
    
    std::cout << "Welcome back! Please put your master password!" << std::endl;
    std::cout << "Password: ";
    std::getline(std::cin, password);
    if (isPasswordCorrect(password, fetchHash())) {
        //std::cout << "passwords match!\n";
        return true; //passwords match
    } else {
        std::cout << "passwords dont match brother, try again\n";
        return false; //passwords dont match brother
    }
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
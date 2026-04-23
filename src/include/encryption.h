#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include "includes.h"
#include <sodium.h>

// Chunk size for file reading/writing (e.g., 4KB)
#define CHUNK_SIZE 4096

class encryption {
public:
    encryption();
    bool firstTimeUser();
    void encrypt();
    void decrypt();

private:
    const char* pathS = path.c_str();
    const char* tempFileS = tempfile.c_str();

    std::string passFile = "untitled.txt";
    std::string userPass; 
    void createPassword();
    std::string fetchHash();
    void genHashtoFile(std::string hashpass); //TODO: make it public to be used later in TUI frontend
    bool verifyUser();
    bool isPasswordCorrect(const std::string& password, const std::string& storedHash);
    std::string hashPassword(const std::string& password);

    bool decryptFile(const char* target_file, const char* source_file, const std::string& password);
    bool encryptFile(const char* target_file, const char* source_file, const std::string& password);
};

#endif
#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include "includes.h"
#include <sodium.h>

// Chunk size for file reading/writing (e.g., 4KB)
#define CHUNK_SIZE 1048576

class encryption {
public:
    encryption();
    bool firstTimeUser();
    void encrypt();
    void decrypt();
    void decryptRAM();
    void encryptRAM();

private:
    const char* pathS = path.c_str();
    const char* tempFileS = tempfile.c_str();

    std::string passFile = "untitled.txt";
    std::string userPass;

    void createPassword();
    std::vector<uint8_t> serializeVector(const std::vector<std::string>& vec);
    std::vector<std::string> deserializeVector(const std::vector<uint8_t>& buffer);

    std::string fetchHash();
    void genHashtoFile(std::string hashpass); //TODO: make it public to be used later in TUI frontend
    bool verifyUser();
    bool isPasswordCorrect(const std::string& password, const std::string& storedHash);
    std::string hashPassword(const std::string& password);

    bool decryptContentToRAM(const filesystem::path& sourcePath, std::vector<std::string>& outVector, const std::string& password);
    bool encryptVectorToFile(const filesystem::path &targetPath, const std::vector<std::string>& dataVector, const std::string& password);
};

#endif
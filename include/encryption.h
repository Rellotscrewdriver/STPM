#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include "includes.h"
#include "plusaes.hpp"
#include "changeSite.h"
class encryption {
public:
    encryption();
    void encrypt();
    void decrypt();

private:
    void encryptFile(
        const std::string& inputFile, 
        const std::string& outputFile, 
        const std::vector<unsigned char>& key, 
        const std::vector<unsigned char>& iv);

    void decryptFile(
        const std::string& inputFile, 
        const std::string& outputFile, 
        const std::vector<unsigned char>& key);

    // --- SETUP: Key and IV ---
    // The Key for AES-128 must be 16 bytes.
    const std::vector<unsigned char> key = {
        0x73, 0x65, 0x63, 0x72, 0x45, 0x74, 0x5f, 0x6b, 0x65, 0x79, 0x5f, 0x31, 0x32, 0x33, 0x34, 0x35
    };

    // The IV for CBC mode must be 16 bytes.
    const std::vector<unsigned char> iv = {
        0x72, 0x61, 0x6e, 0x64, 0x6f, 0x6d, 0x5f, 0x69, 0x76, 0x5f, 0x35, 0x34, 0x33, 0x32, 0x31, 0x30
    };

    //check file functions
    const std::string checkerFileName = "check.txt";
    std::string StoretoFile;
    void replaceCheckFunc(const std::string& flag1, const std::string& oldWord, const std::string& newWord);

    std::vector<std::string> OutCheckFile;
    std::vector<unsigned char> SiteDataVec;
    std::vector<unsigned char> input_buffer;

    bool read_file(
        const std::string& path, 
        std::vector<unsigned char>& buffer);
    bool write_file(
        const std::string& path,
        const std::vector<unsigned char>& buffer);
};

#endif
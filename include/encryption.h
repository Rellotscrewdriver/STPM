#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include "includes.h"
#include <sodium.h>

// Chunk size for file reading/writing (e.g., 4KB)
#define CHUNK_SIZE 4096

class encryption {
public:
    encryption();
    void encrypt();
    void decrypt();

private:
    unsigned char key[crypto_secretstream_xchacha20poly1305_KEYBYTES];    
    const char *tempFile = tempfile.c_str();
    const char *pathC = path.c_str();

    int encryptFile(const char *target_file, const char *source_file);
    int decryptFile(const char *target_file, const char *source_file);
};

#endif
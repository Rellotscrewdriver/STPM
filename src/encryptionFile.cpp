#include "encryption.h"

encryption::encryption(){
    // 2. Generate a fresh, random key
    crypto_secretstream_xchacha20poly1305_keygen(key);

}

//NOTE: tell users to not edit the password file or else it will be damaged
void encryption::encrypt(){
    encryptFile(pathC, tempFile);
    std::rename(tempFile, pathC);
}

void encryption::decrypt(){
    decryptFile(pathC, tempFile);
    std::rename(tempFile, pathC);
}

int encryption::encryptFile(const char *target_file, const char *source_file) 
{

    std::FILE *fp_t = nullptr;
    std::FILE *fp_s = nullptr;

    // Buffers for input and output chunks
    unsigned char buf_in[CHUNK_SIZE];
    // Output buffer is larger: CHUNK_SIZE + crypto_secretstream_xchacha20poly1305_ABYTES (for the tag)
    unsigned char buf_out[CHUNK_SIZE + crypto_secretstream_xchacha20poly1305_ABYTES];
    
    // Header for the stream (must be stored/sent before the ciphertext)
    unsigned char header[crypto_secretstream_xchacha20poly1305_HEADERBYTES];
    
    crypto_secretstream_xchacha20poly1305_state st;
    unsigned long long out_len;
    size_t rlen;
    int eof;
    unsigned char tag = 0; // Default tag for stream chunks

    // 1. Open files
    if ((fp_s = std::fopen(source_file, "rb")) == nullptr) return -1;
    if ((fp_t = std::fopen(target_file, "wb")) == nullptr) {
        std::fclose(fp_s);
        return -1;
    }

    // 2. Initialize the state and get the header
    if (crypto_secretstream_xchacha20poly1305_init_push(&st, header, key) != 0) {
        std::fclose(fp_s);
        std::fclose(fp_t);
        return -1;
    }

    // 3. Write the header to the target file
    if (std::fwrite(header, 1, sizeof header, fp_t) != sizeof header) {
        std::fclose(fp_s);
        std::fclose(fp_t);
        return -1;
    }

    // 4. Process file in chunks
    do {
        // Read a chunk of the source file
        rlen = std::fread(buf_in, 1, sizeof buf_in, fp_s);
        eof = std::feof(fp_s);
        
        // If it's the last chunk, set the TAG_FINAL flag
        tag = eof ? crypto_secretstream_xchacha20poly1305_TAG_FINAL : 0;

        // Encrypt the chunk (push)
        if (crypto_secretstream_xchacha20poly1305_push(&st, buf_out, &out_len,
                                                      buf_in, rlen, NULL, 0, tag) != 0) {
            std::fclose(fp_s);
            std::fclose(fp_t);
            return -1;
        }
        
        // Write the encrypted chunk (with its tag) to the target file
        if (std::fwrite(buf_out, 1, (size_t)out_len, fp_t) != (size_t)out_len) {
            std::fclose(fp_s);
            std::fclose(fp_t);
            return -1;
        }
    } while (!eof);

    // 5. Close files
    std::fclose(fp_s);
    std::fclose(fp_t);
    return 0; // Success
}

// --- Decryption Function ---
int encryption::decryptFile(const char *target_file, const char *source_file) 
{

    std::FILE *fp_t = nullptr;
    std::FILE *fp_s = nullptr;

    // Buffers for input and output chunks
    // Input buffer is larger: CHUNK_SIZE + crypto_secretstream_xchacha20poly1305_ABYTES (for the tag)
    unsigned char buf_in[CHUNK_SIZE + crypto_secretstream_xchacha20poly1305_ABYTES];
    unsigned char buf_out[CHUNK_SIZE];
    
    // Header to be read from the source file
    unsigned char header[crypto_secretstream_xchacha20poly1305_HEADERBYTES];
    
    crypto_secretstream_xchacha20poly1305_state st;
    unsigned long long out_len;
    size_t rlen;
    int eof;
    int ret = -1; // Default return is failure
    unsigned char tag;

    // 1. Open files
    if ((fp_s = std::fopen(source_file, "rb")) == nullptr) return -1;
    if ((fp_t = std::fopen(target_file, "wb")) == nullptr) {
        std::fclose(fp_s);
        return -1;
    }

    // 2. Read the header from the source file
    if (std::fread(header, 1, sizeof header, fp_s) != sizeof header) goto ret_label;

    // 3. Initialize the state for decryption (pull)
    if (crypto_secretstream_xchacha20poly1305_init_pull(&st, header, key) != 0) {
        std::cerr << "Decryption failed: Invalid header/key." << std::endl;
        goto ret_label;
    }

    // 4. Process file in chunks
    do {
        // Read an encrypted chunk (with tag)
        rlen = std::fread(buf_in, 1, sizeof buf_in, fp_s);
        eof = std::feof(fp_s);
        
        // Decrypt the chunk (pull)
        if (crypto_secretstream_xchacha20poly1305_pull(&st, buf_out, &out_len, &tag, 
                                                      buf_in, rlen, NULL, 0) != 0) {
            std::cerr << "Decryption failed: Corrupted chunk or authentication failure." << std::endl;
            goto ret_label; // Authentication failure/corruption detected
        }
        
        // Write the decrypted chunk to the target file
        if (std::fwrite(buf_out, 1, (size_t)out_len, fp_t) != (size_t)out_len) {
            goto ret_label;
        }

        // Check for premature end of file (e.g., file truncated)
        if (tag == crypto_secretstream_xchacha20poly1305_TAG_FINAL && !eof) {
            std::cerr << "Decryption failed: Premature end of stream." << std::endl;
            goto ret_label;
        }
    } while (!eof);

    ret = 0; // Success

ret_label:
    // 5. Close files and return
    std::fclose(fp_s);
    std::fclose(fp_t);
    return ret;
}

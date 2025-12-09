#include "encryption.h"

encryption::encryption(){

    if (sodium_init() < 0) {
        /* panic! the library couldn't be initialized; it is not safe to use */
        std::cout << "Sodium Couldn't be initialized!\n";
    } else {
        std::cout << "Sodium loaded\n";
    }
    
    std::ifstream file(checkerFileName);
    std::string line;

    while (file >> line) {
        OutCheckFile.push_back(line);
    }

    std::cout << "Size: " << OutCheckFile[1] << " Status: " << OutCheckFile[3] << endl;
    std::cout << "\n" << std::boolalpha << (OutCheckFile[3] == "true") << endl;
/*
    if(OutCheckFile[3] == "true"){
        decrypt();
    } else {
        encrypt();
    }
*/
    std::cout << "Size: " << OutCheckFile[1] << " Status: " << OutCheckFile[3] << endl;
}

//NOTE: tell users to not edit the password file or else it will be damaged
void encryption::encrypt(){
    encryptFile(path, path, key, iv);
}

void encryption::decrypt(){
    decryptFile(path, path, key);
}

// Helper function to read a vector to a binary file
bool encryption::read_file(const std::string& path, std::vector<unsigned char>& buffer) {
    std::ifstream file(path, std::ios::binary);
    if (!file) return false;
    buffer.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    return true;
}

// Helper function to write a vector to a binary file
bool encryption::write_file(const std::string& path, const std::vector<unsigned char>& buffer) {
    std::ofstream file(path, std::ios::binary);
    if (!file) return false;
    file.write(reinterpret_cast<const char*>(buffer.data()), buffer.size());
    return true;
}

void encryption::encryptFile(
    const std::string& inputFile,
    const std::string& outputFile,
    const std::vector<unsigned char>& key,
    const std::vector<unsigned char>& iv)
{
    if (!read_file(inputFile, SiteDataVec)) {
        std::cerr << "Error: Could not read input file: " << inputFile << std::endl;
        return;
    }

    const unsigned long encrypted_size = plusaes::get_padded_encrypted_size(SiteDataVec.size());
    std::string eSize = std::to_string(encrypted_size);
    std::vector<unsigned char> encrypted_data(encrypted_size);
    std::vector<unsigned char> iv_copy = iv; // Use a copy as the IV is modified
    
    replaceCheckFunc("size", OutCheckFile[1], eSize);
    replaceCheckFunc("status", OutCheckFile[3], "true");

    // Encrypt the data, casting the IV's data pointer to the required C-style array pointer
    plusaes::encrypt_cbc(
        SiteDataVec.data(), SiteDataVec.size(), 
        key.data(), key.size(), 
        reinterpret_cast<unsigned char(*)[16]>(iv_copy.data()), 
        encrypted_data.data(), encrypted_data.size(), true
    );

    // Prepend the original IV to the ciphertext for storage
    std::vector<unsigned char> output_buffer = iv;
    output_buffer.insert(output_buffer.end(), encrypted_data.begin(), encrypted_data.end());
    rename(tempfile.c_str(), path.c_str());
    
    if (write_file(outputFile, output_buffer)) {
        std::cout << "✅ Successfully encrypted '" << inputFile << "' to '" << outputFile << "'" << std::endl;
    } else {
        std::cerr << "Error: Could not write to output file: " << outputFile << std::endl;
    }
}

void encryption::decryptFile(
    const std::string& inputFile,
    const std::string& outputFile,
    const std::vector<unsigned char>& key)
{
    if (!read_file(inputFile, input_buffer)) {
        std::cerr << "Error: Could not read encrypted file: " << inputFile << std::endl;
        return;
    }

    if (input_buffer.size() < 16) { // File must contain at least the IV
        std::cerr << "Error: Invalid encrypted file format." << std::endl;
        return;
    }

    // Extract the IV from the beginning of the file
    std::vector<unsigned char> iv(input_buffer.begin(), 
    input_buffer.begin() + 16);
    
    // The rest of the buffer is the ciphertext
    std::vector<unsigned char> encrypted_data(
        input_buffer.begin() + 16, 
        input_buffer.end());

    const unsigned long encrypted_size = std::stoul(OutCheckFile[1], nullptr, 10);
    std::vector<unsigned char> decrypted_padded_data(encrypted_size);
    unsigned long padded_size = 0;

    plusaes::decrypt_cbc(
        encrypted_data.data(), encrypted_data.size(), 
        key.data(), key.size(), 
        reinterpret_cast<unsigned char(*)[16]>(iv.data()), 
        decrypted_padded_data.data(), decrypted_padded_data.size(),
        &padded_size
    );

    //rename(tempfile.c_str(), path.c_str());
    replaceCheckFunc("status", OutCheckFile[3], "false");

    if (write_file(outputFile, decrypted_padded_data)) {
        std::cout << "✅ Successfully decrypted '" << inputFile << "' to '" << outputFile << "'" << std::endl;
    } else {
        std::cerr << "Error: Could not write decrypted file: " << outputFile << std::endl;
    }
}

void encryption::replaceCheckFunc(const std::string& flag1, const std::string& oldWord, const std::string& newWord){
    // 2. Open input and output files
    std::ifstream inputFile(checkerFileName);
    std::ofstream tempFile(tempfile);

    std::string line;

    // 3. Read the original file line by line
    while (std::getline(inputFile, line)) {
        // THE CORE LOGIC: Check if the line contains BOTH flag words
        if (line.find(flag1) != std::string::npos && line.find(oldWord) != std::string::npos) {
            
            // This is a target line. Now, replace all occurrences of oldWord.
            size_t pos = 0;
            while ((pos = line.find(oldWord, pos)) != std::string::npos) {
                line.replace(pos, oldWord.length(), newWord);
                pos += newWord.length(); // Move past the replaced word
            }
        }
        // Write the (possibly modified) line to our temporary file
        tempFile << line << '\n';
    }

    // 4. Close the streams
    inputFile.close();
    tempFile.close();

    rename(tempfile.c_str(), checkerFileName.c_str());
}

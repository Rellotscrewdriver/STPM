#include "changeSite.h"

void changeSite::regenPassword(){
    auto rs = std::make_unique<removeSite>(flag1.c_str(), oldWord.c_str());
    auto aps = std::make_unique<addPassSite>(flag1.c_str(), oldWord.c_str());
}

void changeSite::replaceLink(){
    replaceFunc(flag1, oldWord, newWord);
}

void changeSite::replaceEmail(){
    replaceFunc(flag1, oldWord, newWord);
}

//if you have a better idea to replace it with using rapidcsv functions be my guest 
void changeSite::replaceFunc(const std::string& flag1, const std::string& oldWord, const std::string& newWord){
    std::ifstream inputFile(path);
    std::ofstream tempFile(tempfile);

    std::string line;

    // Read the file line by line
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

    rename(tempfile.c_str(), path.c_str());
}

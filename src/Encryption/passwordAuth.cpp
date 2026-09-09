#include "encryption.h"

bool encryption::firstTimeUser(){
  namespace fs = std::filesystem;
  if (!fs::exists(path) || fs::is_empty(path)) {
    // std::cout << "file is empty, creating it" << std::endl;
    createPassword();
    //create an empty file
    // std::ofstream outFile(path);
    // outFile.close();
    encrypt();
    return true; //means the user is new
  } else {
    if(verifyUser()){
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
    } else {
        std::cout << "master Passwords DONT MATCH. try again\n";
        createPassword();
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
        removeTrailingChars(temp);
        password.close();
        return temp; //retrives the hash
    }
    return "FUCK YOU!! Stupid piece of shit";
}

bool encryption::verifyUser(){
    std::string hash = fetchHash();

    while (true) {
        std::string password;
        std::cout << "Welcome back! Please put your master password!" << std::endl;
        std::cout << "Password: ";
        std::getline(std::cin, password);

        removeTrailingChars(password);

        if (isPasswordCorrect(password, hash)) {
            return true; // Passwords match
        }

        std::cout << "passwords dont match brother, try again\n";
    }
}

void encryption::removeTrailingChars(std::string &text){
    // Strip trailing carriage returns/newlines captured from Windows terminals
    while (!text.empty() && (text.back() == '\r' || text.back() == '\n')) {
        text.pop_back();
    }
}
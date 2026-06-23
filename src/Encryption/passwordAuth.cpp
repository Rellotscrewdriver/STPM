#include "encryption.h"

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
        decryptRAM();
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
        //exit(EXIT_FAILURE); //this doesn't clean up objects
        verifyUser();
        return false;
    }
}

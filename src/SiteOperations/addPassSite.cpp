#include "siteOps.h"

bool siteOps::checkEmailVaild(){
    return (email.find("@gmail.com") != std::string::npos) 
    || (email.find("@outlook.com") != std::string::npos) 
    || (email.find("@hotmail.com") != std::string::npos);
}

void siteOps::appendToFile(){
    GeneratePass *pass = new GeneratePass();
    std::string a = email + "," + link + "," + pass->getgeneratedPass();
    siteData.push_back(a);
    std::cout << "Appended " << link << " at " << email << std::endl;
}

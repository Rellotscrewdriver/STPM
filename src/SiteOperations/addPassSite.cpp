#include "siteOps.h"

bool siteOps::checkEmailVaild(){
    return (email.find("@gmail.com") != std::string::npos) 
    || (email.find("@outlook.com") != std::string::npos) 
    || (email.find("@hotmail.com") != std::string::npos);
}

void siteOps::appendToFile(){
    GeneratePass *pass = new GeneratePass();
    siteDataNew.push_back(siteObj(email, link, pass->getgeneratedPass()));
    std::cout << "Appended " << link << " at " << email << std::endl;
}

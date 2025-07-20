#include "addPassSite.h"

bool addPassSite::checkEmailVaild(){
    strEmail = email;
    return (strEmail.find("@gmail.com") != std::string::npos) 
    || (strEmail.find("@outlook.com") != std::string::npos) 
    || (strEmail.find("@hotmail.com") != std::string::npos);
}

void addPassSite::appendToFile(){
    std::ofstream addSite(path, std::ios::app);
    addSite << email << " : " << link << " : " << pass->getgeneratedPass() << endl;
    std::cout << "Appended " << link << " at " << email << std::endl;
    addSite.close();
}

addPassSite::~addPassSite(){
    delete pass;
}
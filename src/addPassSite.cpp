#include "addPassSite.h"

bool addPassSite::checkEmailVaild(){
    strEmail = email;
    return strEmail.find("@") != std::string::npos;
}

void addPassSite::appendToFile(){
    std::ofstream addSite(path, std::ios::app);
    addSite << email << " : " << link << " : " << pass->getgeneratedPass() << endl;
    std::cout << "Appended" << link << "at" << email << std::endl;
    addSite.close();
}

addPassSite::~addPassSite(){
    delete pass;
}
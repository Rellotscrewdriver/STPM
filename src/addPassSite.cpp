#include "addPassSite.h"

bool addPassSite::checkEmailVaild(){
    std::string Stremail = email;
    return Stremail.find("@");
}

void addPassSite::appendToFile(){
    std::ofstream addSite(path, std::ios::app);
    addSite << email << " : " << link << endl;
    std::cout << "Appended" << std::endl;
}
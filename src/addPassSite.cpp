#include "addPassSite.h"

bool addPassSite::checkEmailVaild(){
    return email.find("@");
}

void addPassSite::appendToFile(){
    std::cout << "Appended" << std::endl;
    //std::ofstream addSite("add.txt", std::ios::app);
    //addSite << email << " : " << link;
}
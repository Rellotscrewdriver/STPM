#include "siteOps.h"

void siteOps::appendToFile(){
    GeneratePass *pass = new GeneratePass();
    siteDataNew.push_back(siteObj(email, link, pass->getgeneratedPass()));
    std::cout << "Appended " << link << " at " << email << std::endl;
}

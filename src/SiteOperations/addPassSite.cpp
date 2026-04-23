#include "siteOps.h"

bool siteOps::checkEmailVaild(){
    return (email.find("@gmail.com") != std::string::npos) 
    || (email.find("@outlook.com") != std::string::npos) 
    || (email.find("@hotmail.com") != std::string::npos);
}

void siteOps::appendToFile(){
    rapidcsv::Document doc(path);
    GeneratePass *pass = new GeneratePass();
    std::vector<std::string> addData = {email, link, pass->getgeneratedPass()};
    doc.InsertRow<std::string>(doc.GetRowCount(), addData);
    doc.Save(path);
    delete pass;
    std::cout << "Appended " << link << " at " << email << std::endl;
}

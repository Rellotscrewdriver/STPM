#include "siteOps.h"

void siteOps::appendToFile(){
    GeneratePass *pass = new GeneratePass();
    siteDataNew.push_back(siteObj(email, link, pass->getgeneratedPass()));
    std::cout << "Appended " << link << " at " << email << std::endl;
}

void siteOps::display(const std::vector<siteObj>& data){
    const int credRowWidth = 30;

    std::cout << std::left << std::setw(credRowWidth) << "Email" 
              << std::setw(credRowWidth) << "Sites"
              << std::setw(credRowWidth) << "Password" << std::endl;
    std::cout << std::string(credRowWidth + credRowWidth + credRowWidth, '-') << std::endl;

    for (auto row : data) {
        std::cout << std::left << std::setw(credRowWidth) << row.getEmail() << " | "
                  << std::setw(credRowWidth) << row.getLink() << " | "
                  << std::setw(credRowWidth) << row.getPass() << " | "
                  << std::endl;
    }
}

void siteOps::removeShit(){

    siteDataNew.erase(
        std::remove_if(siteDataNew.begin(), siteDataNew.end(), [this](siteObj& obj) {
            bool compare = (obj.getEmail() == email) && (obj.getLink() == this->link);
            if(compare){
                this->isSiteFound = true;
            }
            return compare; 
        }), 
        siteDataNew.end()
    );

    if(isSiteFound){
        std::cout << "Successfully Removed " << link << " from " << email << "\n";
    } else {
        std::cout << "The Specified Site could not found :(\n";
    }
}
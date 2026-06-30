#include "siteOps.h"

void siteOps::putEveryShitInRAM(){    
    displayInANiceTable(siteDataNew);
};

void siteOps::displayInANiceTable(const std::vector<siteObj>& data){
    const int credRowWidth = 20;

    std::cout << std::left << std::setw(credRowWidth) << "Site Name" 
              << std::setw(credRowWidth) << "Username"
              << std::setw(credRowWidth) << "Password" << std::endl;
    std::cout << std::string(credRowWidth + credRowWidth + credRowWidth, '-') << std::endl;

    for (auto row : data) {
        std::cout << std::left << std::setw(credRowWidth) << row.getEmail() 
                  << std::setw(credRowWidth) << row.getLink()
                  << std::setw(credRowWidth) << row.getPass() 
                  << std::endl;
    }
}
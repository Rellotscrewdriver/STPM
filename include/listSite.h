#pragma once

#include "includes.h"

class listSite {
public:
    listSite();

/*    listSite(char* flag1) : strFlag(flag1){
        std::cout << "Show it either based on email or link" << "\n";
    };
*/
private:
    std::string strFlag;
    char separator = ',';
    std::vector<std::string> addLines;
    void displayInANiceTable(const std::vector<std::string>& all_lines, int columns = 3);
    //void safeguard();
    //void showSiteBasedOnEmail();
    void showEmailBasedOnLink();
};
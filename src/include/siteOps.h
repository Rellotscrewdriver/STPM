#pragma once

#include "includes.h"
#include "genPass.h"

class siteOps {
public:
    //for add & remove
    siteOps(std::string &emailAddress, std::string &LinkName);
    //for changes
    siteOps(std::string &flag, std::string &oldStr, std::string &newStr);
    //for list
    siteOps();

    //wrapper functions
    void addSite();
    void removeSite();
    void changeSite();
    
private:
    std::string email, link, mFlag, mOldStr, mNewStr;
    
    void appendToFile();
    void removeShit();
    bool checkEmailVaild();

    char separator = ',';
    std::vector<std::string> addLines;
    void putEveryShitInRAM();
    void displayInANiceTable(const std::vector<std::string>& all_lines, int columns = 3);

    void regenPassword();
    void replaceLink();
    void replaceEmail();
    void replaceFunc(const std::string& flag1, const std::string& oldWord, const std::string& newWord);


};

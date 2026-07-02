#pragma once

#include "includes.h"
#include "genPass.h"
#include "siteObj.h"
#include "validation.h"

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
    bool checkEmailVaild(std::string flag);
    bool checkLinkVaild(std::string flag);
    void hugeRegexCheck();

    enum idenStr replaceWhat;
    char separator = ',';
    std::vector<std::string> addLines;
    void putEveryShitInRAM();
    void displayInANiceTable(const std::vector<siteObj>& data);

    void regenPassword();
    void replaceLink();
    void replaceEmail();
};

#pragma once

#include "includes.h"
#include "genPass.h"

class siteOps {
public:
    //for add & remove
    siteOps(std::string &emailAddress, std::string &LinkName);
    //for changes
    siteOps(int SiteNum, std::string &flag, std::string &oldStr, std::string &newStr);
    //for list
    siteOps(int SiteNum, std::string &flag);

    siteOps();
    //~siteOps();

    //wrapper functions
    void addSite();
    void removeSite();
    void changeSite();
    void listSite();
    
private:
    std::string email, link, flag, oldStr, newStr;
    
    void appendToFile();
    void removeShit();
    bool checkEmailVaild();

};

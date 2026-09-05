#pragma once

#include "includes.h" 
#include "../genPass/genPass.h"

class siteObj {
public:
    siteObj(std::string Email, std::string siteName, std::string passStr) : link(siteName), email(Email), password(passStr){};

    std::string &getEmail(){return email;}
    std::string &getLink(){return link;}
    std::string &getPass(){return password;}
    std::string getRawString(){
        return email + "," + link + "," + password;
    }
    // void setPass(){ password = gp.getgeneratedPass(); }
private:

    std::string email;
    std::string link;
    std::string password;
};

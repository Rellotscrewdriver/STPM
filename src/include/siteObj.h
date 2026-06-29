#pragma once

#include "includes.h" 

class siteObj {
public:
    siteObj(std::string Email, std::string siteName, std::string passStr) : link(siteName), email(Email), password(passStr){};

    std::string &getEmail(){return email;}
    std::string &getLink(){return link;}
    std::string getPass(){return password;}

private:
    std::string email;
    std::string link;
    std::string password;
};

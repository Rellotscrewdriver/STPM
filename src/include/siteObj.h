#pragma once

#include "includes.h" 

/**
 * this class stores three type of credentials: email, link and password
 */
class siteObj {
public:
    /**
     * this constructor initializes the three strings given by arguements to private variables
     */
    siteObj(std::string Email, std::string siteName, std::string passStr) : link(siteName), email(Email), password(passStr){}

    /**
     * this member fetches and sets the email
     */    
    std::string &getEmail(){return email;}

    /**
     * this member fetches and sets the link
     */    
    std::string &getLink(){return link;}

    /**
     * this member fetches and sets the password, mainly used in TUI frontend
     */    
    std::string &getPass(){return password;}

    /**
     * this member converts it to raw string, used in converting objects into raw string vector
     */    
    std::string getRawString(){
        return email + "," + link + "," + password;
    }

private:

    std::string email;
    std::string link;
    std::string password;
};

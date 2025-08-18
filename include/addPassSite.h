#pragma once

#include "includes.h"
#include "genPass.h"

class addPassSite {
public:
    addPassSite(char* emailAddress, char* LinkName) : email(emailAddress), link(LinkName){
        if(checkEmailVaild()){
            appendToFile();
        } else {
            std::cout << "The Email address is not vaild";            
        }
    };
    ~addPassSite();
private:
    GeneratePass *pass = new GeneratePass();
    bool checkEmailVaild();
    void appendToFile();
    char* email;
    char* link;    
    std::string strEmail;
};

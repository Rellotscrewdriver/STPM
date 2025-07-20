#ifndef ADDPASSITE_H
#define ADDPASSITE_H

#include "dectargs.h"
#include "genPass.h"
#include <fstream>

extern inline std::string path = "add.txt";

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

#endif
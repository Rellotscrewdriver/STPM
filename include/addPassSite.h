#ifndef ADDPASSITE_H
#define ADDPASSITE_H

#include "dectargs.h"
#include <fstream>

class addPassSite {
public:
    addPassSite(char* emailAddress, char* LinkName) : email(emailAddress), link(LinkName){
        if(!checkEmailVaild()){
            std::cout << std::boolalpha << " " << checkEmailVaild() << std::endl;
            std::cout << "The Email address is not vaild";
        } else {
            std::cout << std::boolalpha << " " << checkEmailVaild() << std::endl;
            appendToFile();
        }
    };

private:
    bool checkEmailVaild();
    void appendToFile();
    std::string email;
    std::string link;
};

#endif
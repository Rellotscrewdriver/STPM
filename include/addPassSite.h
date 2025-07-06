#ifndef ADDPASSITE_H
#define ADDPASSITE_H

#include "dectargs.h"
#include "genPass.h"
#include <fstream>

class addPassSite {
public:
    addPassSite(char* emailAddress, char* LinkName) : email(emailAddress), link(LinkName){
        if(!checkEmailVaild()){
            std::cout << "The Email address is not vaild";
        } else {
            appendToFile();
        }
    };
    ~addPassSite();
private:
    GeneratePass *pass = new GeneratePass();
    bool checkEmailVaild();
    void appendToFile();
    char* email;
    char* link;
    static inline std::string path = "add.txt";
    std::string strEmail;
};

#endif
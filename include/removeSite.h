#ifndef REMOVESITE_H
#define REMOVESITE_H

#include "dectargs.h"
//#include "includes.h"
#include "genPass.h"

#include <vector>

class removeSite {
public:
    removeSite(char* emailAddress, char* LinkName) : email(emailAddress), link(LinkName){finalRemoveIt(fileName, link);};
private:
    char* email;
    char* link;
    std::string eraseLineLink;
    std::string eraseLineEmail;
    void finalRemoveIt(std::string path, char* eraseLine);
    std::string fileName = "add.txt"; //temporary to make it working

    std::string line;
};

#endif
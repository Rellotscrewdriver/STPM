#ifndef REMOVESITE_H
#define REMOVESITE_H

#include "dectargs.h"
//#include "includes.h"
#include "genPass.h"


class removeSite {
public:
    removeSite(char* emailAddress, char* LinkName) : email(emailAddress), link(LinkName){finalRemoveIt();};
private:
    char* email;
    char* link;

    void finalRemoveIt();
    //std::string fileName = "add.txt"; //temporary to make it working

    std::string line;

    std::string eraseLineLink = link;
    std::string eraseLineEmail = email;
    int posLink;
    int posEmail;
};

#endif
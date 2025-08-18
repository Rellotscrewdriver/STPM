#pragma once

#include "includes.h"

class removeSite {
public:
    removeSite(char* emailAddress, char* LinkName) : email(emailAddress), link(LinkName){finalRemoveIt();};
private:
    char* email;
    char* link;
    void finalRemoveIt();

    std::string line;

    std::string eraseLineLink = link;
    std::string eraseLineEmail = email;
    int posLink;
    int posEmail;
};


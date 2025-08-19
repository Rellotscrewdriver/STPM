#pragma once

#include "includes.h"

class removeSite {
public:
    removeSite(const char* emailAddress, const char* LinkName) : email(emailAddress), link(LinkName){finalRemoveIt();};
private:
    const char* email;
    const char* link;
    void finalRemoveIt();

    std::string line;

    std::string eraseLineLink = link;
    std::string eraseLineEmail = email;
    int posLink;
    int posEmail;
};


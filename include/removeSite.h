#ifndef REMOVESITE_H
#define REMOVESITE_H

#include "dectargs.h"
//#include "includes.h"
#include "genPass.h"

#include <vector>

class removeSite {
public:
    removeSite(char* LinkName) : link(LinkName){finalRemoveIt(fileName, link);};
private:
    char* link;
    std::string linkStr;
    void finalRemoveIt(std::string path, char* eraseLine);
    std::string fileName = "add.txt"; //temporary to make it working

    std::string line;
    std::vector<std::string> AddLines;
};

#endif
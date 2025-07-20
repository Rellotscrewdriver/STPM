#ifndef GENERATEPASS_H
#define GENERATEPASS_H

#include "includes.h"

class GeneratePass {
public:
    GeneratePass() = default;
    std::string getgeneratedPass();

private:
    std::string genPass();
    std::random_device rd;  // Seed source
    std::string passchars = "abcdefghijklmnopqrstuvwxyz123456789!@#$%&*";
    std::string passStr;
    int passLen = 15;
    int randonNum;
};

#endif
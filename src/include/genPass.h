#pragma once

#include "includes.h"

class GeneratePass {
public:
    GeneratePass() = default;
    std::string getgeneratedPass();

private:
    std::string genPass();
    std::random_device rd;  // Seed source
    std::string passchars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789!@#$%&*";
    std::string passStr;
    int passLen = 15;
    int randonNum;
};

#pragma once

#include "includes.h"

/**
 * generates a unique random number
 */
class GeneratePass {
public:
    GeneratePass() = default;
    /**
     * This is a wrapper or getter function of genPass() function
     * 
     * @return genPass() function
     */
    std::string getgeneratedPass();

private:
    /**
     * this generates a unique string using std::mt19937 using std::random_device
     * which is the modern C++ alternative
     * 
     * @return string of random characters
     */
    std::string genPass();
    std::random_device rd;  // Seed source
    // TODO: add captial letters
    std::string passchars = "abcdefghijklmnopqrstuvwxyz123456789!@#$%&*";
    std::string passStr;
    int passLen = 15;
    int randonNum;
};
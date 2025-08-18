#pragma once

#include "includes.h"
#include "genPass.h"

class changeSite {
public: 
    changeSite(char* email, char* link) : 
    flag1(email), oldWord(link){regenPassword();};

    changeSite(char* flag, char* flag2, char* flag3) : 
    flag1(flag), oldWord(flag2), newWord(flag3){
        if((oldWord.find("@") != std::string::npos) && (oldWord.find(".") != std::string::npos)){
            std::cout << "Replaced Link" << std::endl;
            replaceLink();
        } else {
            std::cout << "Replaced Email" << std::endl;
            replaceEmail();
        }
    };

private:
    std::string oldWord;
    std::string flag1;
    std::string newWord;

    void regenPassword();
    void replaceLink();
    void replaceEmail();
    void tempFunction(const std::string& flag1, const std::string& oldWord, const std::string& newWord);
};
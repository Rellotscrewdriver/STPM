#include "siteOps.h"

siteOps::siteOps(std::string &emailAddress, std::string &LinkName) : email(emailAddress), link(LinkName){
    if(!checkEmailVaild()){
        std::cout << "The Email address is not vaild\n";
        exit(EXIT_FAILURE);                   
    }
}

siteOps::siteOps(std::string &flag, std::string &oldStr, std::string &newStr) : mFlag(flag), mOldStr(oldStr), mNewStr(newStr){}

siteOps::siteOps(){
    putEveryShitInRAM();
}

void siteOps::addSite(){
    appendToFile();
}

void siteOps::removeSite(){
    removeShit();
}

void siteOps::changeSite(){
    if(!mNewStr.empty()){
        std::cout << "Replacing: " << mFlag << std::endl;
        if((mFlag.find("@") != std::string::npos) && (mFlag.find(".") != std::string::npos)){
            std::cout << "Replaced Link" << std::endl;
            replaceLink();
        } else {
            std::cout << "Replaced Email" << std::endl;
            replaceEmail();
        }
    } else {
        std::cout << "Regenerating and Replacing Password\r" << std::endl;
        regenPassword();
        std::cout << "Replaced Password" << std::endl;        
    }
}

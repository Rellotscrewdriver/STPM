#include "siteOps.h"

siteOps::siteOps(std::string &emailAddress, std::string &LinkName) : email(emailAddress), link(LinkName){
    if(!checkEmailVaild(email) || !checkLinkVaild(link)){
        std::cout << "The Email address or link name is not vaild\n";
        exit(EXIT_FAILURE);                  
    }
}

siteOps::siteOps(std::string &flag, std::string &oldStr, std::string &newStr) : mFlag(flag), mOldStr(oldStr), mNewStr(newStr){
    hugeRegexCheck();
}

siteOps::siteOps(){
    putEveryShitInRAM();
}

bool siteOps::checkEmailVaild(std::string flag){
    regexValid rv;
    return rv.checkemail(flag);
}

bool siteOps::checkLinkVaild(std::string flag){
    regexValid rv;
    return rv.checklink(flag);
}

void siteOps::addSite(){
    appendToFile();
}

void siteOps::removeSite(){
    removeShit();
}

void siteOps::hugeRegexCheck(){
    regexValid rv;
    if(rv.identify(mFlag) == isEmail || rv.identify(mOldStr) == isEmail){

    } else if(rv.identify(mFlag) == isLink || rv.identify(mOldStr) == isLink){
        
    } else {
        std::cout << "The flag/current Email address or link name is not vaild\n";
        exit(EXIT_FAILURE);
    }
    // if( (!checkEmailVaild(mFlag) || !checkLinkVaild(mOldStr)) 
    //     || (!checkEmailVaild(mOldStr) || !checkLinkVaild(mFlag))){
    //     std::cout << "The flag/current Email address or link name is not vaild\n";
    //     exit(EXIT_FAILURE);                  
    // } else if(){

    // }
}

void siteOps::changeSite(){
    if(!mNewStr.empty()){
        std::cout << "Replacing: " << mFlag << std::endl;
        regexValid rv;
        if(rv.identify(mFlag) == isEmail){
            std::cout << "Replacing Link" << std::endl;
            replaceLink();
        } else if(rv.identify(mFlag) == isLink) {
            std::cout << "Replacing Email" << std::endl;
            replaceEmail();
        } else {
            std::cout << "The new Email or Link is not vaild\n";
            exit(EXIT_FAILURE);                              
        }
    } else {
        std::cout << "Regenerating and Replacing Password\r" << std::endl;
        regenPassword();
        std::cout << "Replaced Password" << std::endl;        
    }
}

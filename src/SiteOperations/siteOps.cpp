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
    idenStr regexCheckFlag = rv.identify(mFlag);
    idenStr regexCheckOldWord = rv.identify(mOldStr);
    idenStr regexCheckNewWord = rv.identify(mNewStr);

    if(regexCheckFlag == isLink && 
        (regexCheckOldWord == isEmail && regexCheckNewWord == isEmail)
    ){
        //sets to change email
        replaceWhat = isEmail;
    } else if(regexCheckFlag == isEmail && 
        (regexCheckOldWord == isLink && regexCheckNewWord == isLink)
    ){
        //sets to change link
        replaceWhat = isLink;
    } else if(regexCheckFlag == isEmail && (regexCheckOldWord == isLink && mNewStr.empty())){
        //simply just regenerate password
        replaceWhat = justGenPass;
    } else {
        std::cout << "Email addresses or links are not vaild format\n";
        exit(EXIT_FAILURE);
    }
}

void siteOps::changeSite(){
    if(!mNewStr.empty()){
        // std::cout << "Replacing Flag: " << mFlag << std::endl;
        if(replaceWhat == isLink){
            std::cout << "Replacing Link" << std::endl;
            replaceLink();
        } else if(replaceWhat == isEmail) {
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

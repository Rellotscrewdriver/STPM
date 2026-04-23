#include "siteOps.h"

siteOps::siteOps(std::string &emailAddress, std::string &LinkName) : email(emailAddress), link(LinkName){
    if(!checkEmailVaild()){
        std::cout << "The Email address is not vaild\n";
        exit(EXIT_FAILURE);                   
    }
}

void siteOps::addSite(){
    appendToFile();
}

void siteOps::removeSite(){
    removeShit();
}

void siteOps::changeSite(){

}

void siteOps::listSite(){

}
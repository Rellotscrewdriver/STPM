#include "genPass.h"

std::string GeneratePass::getgeneratedPass(){
    return genPass();
}

std::string GeneratePass::genPass(){
    passStr.clear();
    
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> diss(8, 20); //min length: 8, max length: 20
    passLen = diss(gen); 
    for(int i = 0; i < passLen; i++){
        std::uniform_int_distribution<> dis(0, passchars.length());
        randonNum = dis(gen);
        passStr += (passchars[randonNum]);
    }
    return passStr;
}
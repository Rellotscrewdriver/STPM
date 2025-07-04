#include "genPass.h"

std::string GeneratePass::getgeneratedPass(){
    return genPass();
}

std::string GeneratePass::genPass(){
    std::mt19937 gen(rd());
    for(int i = 0; i < passLen; i++){
        std::uniform_int_distribution<> dis(0, passchars.length());
        randonNum = dis(gen);
        passStr += (passchars[randonNum]);
    }
    return passStr;
}
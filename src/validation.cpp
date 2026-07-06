#include "validation.h"

bool regexValid::checkemail(std::string_view refEmail){
    return RE2::FullMatch(refEmail, emailPattern);
}

bool regexValid::checklink(std::string_view refLink){
    return RE2::FullMatch(refLink, linkNamePattern);
}

idenStr regexValid::identify(std::string_view str){
    if(checkemail(str)){
        return isEmail;
    } else if(checklink(str)){
        return isLink;
    }
    return notValid;
};
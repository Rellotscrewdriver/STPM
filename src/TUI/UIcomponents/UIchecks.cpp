#include "../tui.h"
#include "../regexValid/validation.h"

bool TUIFrontEnd::validateInputs(const std::string& email, const std::string& site) {
    regexValid rv;
    if (email.empty() || site.empty()) {
        validationMsg = "Email or Site cannot be empty!";
        isValidCredentials = false;
        return false;
    }
    
    // Example basic checks (or use std::regex)
    if (!rv.checkemail(email)) {
        validationMsg = "Invalid email format";
        isValidCredentials = false;
        return false;
    }

    if (!rv.checklink(site)) {
        validationMsg = "Invalid site format";
        isValidCredentials = false;
        return false;
    }
    
    isValidCredentials = true;
    validationMsg = ""; // Clear error when valid
    return true;
}

bool TUIFrontEnd::validateNewMasterPass(){
    if(masterPassT == masterPassTDup){
        masterPassT.clear();
        masterPassTDup.clear();
        isValidPassword = true;
        db.saveHash(masterPassT);
        return true;
    }
    
    isValidPassword = false;
    passMsg = "Passwords don't match!";
    return false;
}

bool TUIFrontEnd::validateMasterPass(){
    if(db.verify(masterPassT)){
        masterPassT.clear();
        return true;
    }
    
    passMsg = "invalid Password!";
    return false;
}


void TUIFrontEnd::firstTime(){
    namespace fs = std::filesystem;
    if (!fs::exists(path) || fs::is_empty(path)){
        activeLayer = layers::newUserD;
    } else {
        activeLayer = layers::masterPassD;
    }
}
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

void TUIFrontEnd::validateMasterPass(){
    
}
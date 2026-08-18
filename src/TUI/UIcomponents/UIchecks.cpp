#include "../tui.h"

bool TUIFrontEnd::validateEmail(const std::string& email) {
    if (email.empty()) {
        emailErrorMsg = "Email cannot be empty!";
        isEmailValid = false;
        return false;
    }
    // Example basic checks (or use std::regex)
    if (email.find('@') == std::string::npos || email.find('.') == std::string::npos) {
        emailErrorMsg = "Invalid email format (missing '@' or '.')";
        isEmailValid = false;
        return false;
    }
    
    isEmailValid = true;
    emailErrorMsg = ""; // Clear error when valid
    return true;
}

bool TUIFrontEnd::validateSite(const std::string& site) {
    if (site.empty()) {
        siteErrorMsg = "Site cannot be empty!";
        isSiteValid = false;
        return false;
    }
    // Example basic checks (or use std::regex)
    // if () {
    //     emailErrorMsg = "Invalid email format (missing '@' or '.')";
    //     return false;
    // }
 
    isSiteValid = true;
    siteErrorMsg = ""; // Clear error when valid
    return true;
}
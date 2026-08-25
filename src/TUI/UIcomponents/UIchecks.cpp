#include "../tui.h"

bool TUIFrontEnd::validateInputs(const std::string& email, const std::string& site) {
    if (email.empty()) {
        validationMsg = "Email cannot be empty!";
        isValidCredentials = false;
        return false;
    }
    // Example basic checks (or use std::regex)
    if (email.find('@') == std::string::npos || email.find('.') == std::string::npos) {
        validationMsg = "Invalid email format (missing '@' or '.')";
        isValidCredentials = false;
        return false;
    }

    if (site.empty()) {
        validationMsg = "Site cannot be empty!";
        isValidCredentials = false;
        return false;
    }
    
    validationMsg = true;
    validationMsg = ""; // Clear error when valid
    return true;
}

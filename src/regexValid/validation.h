#pragma once

#include "includes.h" 
#include <re2/re2.h>

/**
 * this enum is used for identifying what the user has given
 * and what to do with it, mainly used in change mode in commandline
 */
enum idenStr {
    isEmail,
    isLink,
    justGenPass,
    notValid,
};

/**
 * this class verifies the validity of credentials like email and link 
 */
class regexValid {
public:
    regexValid() = default;

    /**
     * this member function checks for email validity
     * 
     * @param email_reference
     * @returns true if matches, else false
     */
    bool checkemail(std::string_view refEmail);

    /**
     * this member function checks for link validity
     * 
     * @param link_reference
     * @returns true if matches, else false
     */    
    bool checklink(std::string_view refLink);

    /**
     * this member function identifies what given arguement is
     * 
     * @param string_to_compare
     * @returns returns an enum like isEmail, isLink, notValid
     */    
    idenStr identify(std::string_view str);

private:
    /**
     * this is a regex pattern used for validating email
     */
    inline static const re2::RE2 emailPattern = R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})";

    /**
     * this is a regex pattern used for validating link
     */
    inline static const re2::RE2 linkNamePattern = R"((([a-zA-Z0-9-]+\.)+[a-zA-Z]{2,}))";
};

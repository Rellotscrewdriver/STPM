#pragma once

#include "includes.h"
#include "../genPass/genPass.h"
#include "siteObj.h"
#include "../regexValid/validation.h"

/**
 * this is the class where it handles the credentials operations
 */
class siteOps {
public:
    /**
     * this constructor takes email and links parameters and passes them to objects
     * it mainly used for adding and removing modes
     * @param emailAddress
     * @param LinkName
     * 
     * @tip
     * this function also verifies whether the email is vaild or not
     */
    siteOps(std::string &emailAddress, std::string &LinkName);
    
    /**
     * this constructor takes a flag and an old parameter & the new parameter which replaces the old one and passes them to objects
     * it mainly used for changing email, site or regenerating passwords
     * @param flag
     * @param old_string
     * @param new_string
     * 
     * @info
     * this function doesn't do anything
     */
    siteOps(std::string &flag, std::string &oldStr, std::string &newStr);
    
    /**
     * this takes nothing, it's only used for listing data
     */
    siteOps();

    /**
     * this function is a wrapper or setter functions which are called from outside the objects 
     */
    void addSite();
    
    /**
     * this function is a wrapper or setter functions which are called from outside the objects 
     */
    void removeSite();
    
    /**
     * this function is a wrapper or setter functions which are called from outside the objects 
     */
    void changeSite();
    
private:
    std::string email, link, mFlag, mOldStr, mNewStr;
    bool isSiteFound = false;
    enum idenStr replaceWhat;
    char separator = ',';
    
    /**
     * this function adds the site to the last position
     */
    void appendToFile();
    
    /**
     * this function removes the site by looking for exact siteName and Email and then deletes it
     */
    void removeShit();
    
    /**
     * this function checks whether email is vaild or not.
     */
    bool checkEmailVaild(std::string flag);
    bool checkLinkVaild(std::string flag);
    void hugeRegexCheck();

    std::vector<std::string> addLines;
    /**
     * this function splits the thing into words by a separator
     */
    void putEveryShitInRAM();

    /**
     * this function prints out everything in a nice table
     */
    void displayInANiceTable(const std::vector<siteObj>& data);

    /**
     * this site re-generates the password by deleting and adding the site
     * maybe I should uhh
     */
    void regenPassword();
    
    /**
     * this method replaces link of the specific email
     * it's done like that avoid changing links of the same email name
     */
    void replaceLink();
    
    /**
     * this method replaces email of the specific link
     * it's done like that avoid changing links of the same link name
     */
    void replaceEmail();
};

#pragma once

#include "includes.h"
#include "../Encryption/encryption.h"
#include "clip.h"

/**
 * contains operations to be performed on data, they are redirected to backend
 */
class dataManager {
public:
    dataManager() = default;
    
    /** 
     * an enum to determine what is copied
     */ 
    enum copyData {
        copyEmail,
        copySite,
        copyPass
    };

    /** 
     * this gives user feedback on what is copied
     */ 
    std::string statusMessage = "nothing was copied to clipboard";

    /** 
     * these are instructions given to the user at TUI session
     */ 
    const std::string copyIns = "Press 'c' to copy Email | Press 'v' to copy Site | Press 'b' to copy Password";

    /** 
     * these are instructions given to the user at TUI session
     */ 
    const std::string mainNavText = "Shortcuts: [↑/↓] Navigate  [Enter] Edit  [n] Add  [d] Delete  [Ctrl+s] Save [q] Quit";

    /** 
     * these are instructions given to the user at TUI session
     */ 
    const std::string dialogNavText1 = "Navigation: [↑/↓] Switch Fields  [←/→] Select Options";

    /** 
     * these are instructions given to the user at TUI session
     */ 
    const std::string dialogNavText2 = "Navigation: [←/→] Select Options";    

    /**
     * empty menu entries for the TUI menu to function properly
     */
    std::vector<std::string> menuEntries;
    
    /**
     * updates menu entries for the TUI menu to function properly
     */
    void updateMenuEnteries();

    /**
     * determine what and where to copy the data from and give feedback to user when it is copied
     * 
     * @param type
     * @param selectedRow 
     */
    void copyCreds(copyData type, int selectedRow);

    /**
     * add a row to siteData vector directly
     * 
     * @param email
     * @param site
     * @param password 
     */
    void addRow(std::string &email, std::string &site, std::string &pass);

    /**
     * delete a row to siteData vector directly
     * 
     * @param selectedRow 
     */
    void deleteRow(int selectedRow);
    
    /**
     * encrypts and saves the global data to disk
     */
    void saveData();

    /**
     * decrypts and loads the global data to RAM
     */    
    void loadData();

    /**
     * saves the hash of master password to disk
     * 
     * @param MasterPassword
     */    
    void saveHash(std::string materPass);

    /**
     * verifies the hash given by user in TUI session
     * 
     * @param OldMasterPassword
     */    
    bool verify(std::string oldPass);

private:
    encryption enc;

    /**
     * copies the info into respective OS clipboard using clip library
     * if the user is using wayland, then the info is copied manually through wl-copy
     * 
     * @param info
     */        
    void copyToClipBoard(const std::string &info);
};
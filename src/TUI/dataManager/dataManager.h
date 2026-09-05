#pragma once

#include "includes.h"
#include "../Encryption/encryption.h"
#include "clip.h"

class dataManager {
public:
    dataManager() = default;
    
    enum copyData {
        copyEmail,
        copySite,
        copyPass
    };

    std::string statusMessage = "nothing was copied to clipboard";
    std::string copyIns = "Press 'c' to copy Email | Press 'v' to copy Site | Press 'b' to copy Password";
    const std::string mainNavText = "Shortcuts: [↑/↓] Navigate  [Enter] Edit  [n] Add  [d] Delete  [Ctrl+s] Save [q] Quit";
    const std::string dialogNavText1 = "Navigation: [↑/↓] Switch Fields  [←/→] Select Options";
    const std::string dialogNavText2 = "Navigation: [←/→] Select Options";    


    std::vector<std::string> menuEntries;
    void updateMenuEnteries();


    void copyCreds(copyData type, int selectedRow);

    //operations
    void addRow(std::string &email, std::string &site, std::string &pass);
    void deleteRow(int selectedRow);

    //loading data    
    void saveData();
    void loadData();

    //password hashing
    void saveHash(std::string materPass);
    bool verify(std::string oldPass);

private:
    encryption enc;
    void copyToClipBoard(const std::string &info);
};
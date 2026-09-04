#include "dataManager.h"

void dataManager::addRow(std::string &email, std::string &site, std::string &pass){
    siteDataNew.push_back(siteObj(email, site, pass));
    menuEntries.push_back("");
}

void dataManager::deleteRow(int selectedRow){
    siteDataNew.erase(siteDataNew.begin() + selectedRow);
    menuEntries.erase(menuEntries.begin() + selectedRow);
    
    // Ensure selection stays within bounds
    if (selectedRow >= siteDataNew.size()) {
        selectedRow = siteDataNew.size();
    }
}

void dataManager::saveData(){
    enc.encrypt();
}

void dataManager::loadData(){
    enc.decrypt();
}

bool dataManager::verify(std::string oldPass){
    return enc.isPasswordCorrect(oldPass, enc.fetchHash());
}

void dataManager::saveHash(std::string materPass){
    enc.genHashtoFile(materPass);
}

void dataManager::updateMenuEnteries(){
    menuEntries.clear();
    if (siteDataNew.empty()) {
        // Keep 1 dummy entry so ftxui::Menu doesn't hang
        menuEntries.push_back("Empty");
    } else {
        for (const auto& item : siteDataNew) {
            menuEntries.push_back("");
        }
    }
}
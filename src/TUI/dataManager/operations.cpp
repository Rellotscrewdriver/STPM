#include "dataManager.h"

void dataManager::addRow(std::string &email, std::string &site, std::string &pass){
    siteDataNew.push_back(siteObj(email, site, pass));
    menu_entries.push_back("");
}

void dataManager::deleteRow(int selectedRow){
    siteDataNew.erase(siteDataNew.begin() + selectedRow);
    menu_entries.erase(menu_entries.begin() + selectedRow);
    
    // Ensure selection stays within bounds
    if (selectedRow >= siteDataNew.size()) {
        selectedRow = siteDataNew.size() - 1;
    }
}

void dataManager::saveData(){
    enc.encrypt();
}

void dataManager::updateMenuEnteries(){
    menu_entries.clear();
    if (siteDataNew.empty()) {
        // Keep 1 dummy entry so ftxui::Menu stays focusable
        menu_entries.push_back("Empty");
    } else {
        for (const auto& item : siteDataNew) {
            menu_entries.push_back(""); // Or whatever key you use
        }
    }

    // for (size_t i = 0; i < data.size(); i++) {
    //     // Push empty strings; the text is handled by the transform function above
    //     menu_entries.push_back(""); 
    // }
}
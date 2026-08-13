#include "dataManager.h"

void dataManager::addRow(){
    data.push_back({"007", "James Bond", "Secret Service Agent"});
    menu_entries.push_back("");
}

void dataManager::deleteRow(int selectedRow){
    data.erase(data.begin() + selectedRow);
    menu_entries.erase(menu_entries.begin() + selectedRow);
    
    // Ensure selection stays within bounds
    if (selectedRow >= data.size()) {
        selectedRow = data.size() - 1;
    }
}

void dataManager::saveData(){
    //encrypt the data here
}
#include "tui.h"


void TUIFrontEnd::addRow(){
    data.push_back({"007", "James Bond", "Secret Service Agent"});
    menu_entries.push_back("");
}

void TUIFrontEnd::deleteRow(){
    data.erase(data.begin() + selected_row);
    menu_entries.erase(menu_entries.begin() + selected_row);
    
    // Ensure selection stays within bounds
    if (selected_row >= data.size()) {
        selected_row = data.size() - 1;
    }
}

void TUIFrontEnd::saveData(){
    //encrypt the data here
}
#include "../tui.h"

Element TUIFrontEnd::menuRowEntry(const EntryState &state){
    if (state.index >= db.data.size()){
        return text("");
    }
    
    const auto& row = db.data[state.index];
    Element rowElement = hbox({
        paragraph(row.id) | size(WIDTH, EQUAL, 20),
        paragraph(row.name) | flex, 
        paragraph(row.role) | size(WIDTH, EQUAL, 20),
    });
    
    if (state.focused){
        //TODO: put this in style.cpp
        rowElement = rowElement | bgcolor(Color::Blue) | color(Color::Black) | bold;
    }
    
    return rowElement;
}

void TUIFrontEnd::updateMenuEnteries(){
    db.menu_entries.clear();
    for (size_t i = 0; i < db.data.size(); i++) {
        // Push empty strings; the text is handled by the transform function above
        db.menu_entries.push_back(""); 
    }
}
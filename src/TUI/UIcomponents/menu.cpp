#include "../tui.h"

Element TUIFrontEnd::menuRowEntry(const EntryState &state){
    if (siteDataNew.empty()) {
        return text(" (No Entries) ") | dim | center;
    }
    
    if (state.index >= siteDataNew.size()){
        return text("");
    }
    
    auto& row = siteDataNew[state.index];
    Element rowElement = hbox({
        paragraph(row.getEmail()) | size(WIDTH, EQUAL, 20),
        paragraph(row.getLink()) | flex, 
        paragraph(row.getPass()) | size(WIDTH, EQUAL, 20),
    });
    
    if (state.focused){
        rowElement = rowElement | bgcolor(Color::Blue) | color(Color::Black) | bold;
    }
    
    return rowElement;
}


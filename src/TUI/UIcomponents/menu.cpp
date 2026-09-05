#include "../tui.h"

Element TUIFrontEnd::menuRowEntry(const EntryState &state){
    if (siteDataNew.empty()) {
        return paragraphAlignCenter(" (No Entries Found) ") | dim | center;
    }
    
    if (state.index >= siteDataNew.size()){
        return text("");
    }
    
    auto& row = siteDataNew[state.index];
    Element rowElement = hbox({
        paragraphAlignLeft(row.getEmail()) | size(WIDTH, EQUAL, 30),
        paragraphAlignCenter(row.getLink()) | flex, 
        paragraphAlignCenter(row.getPass()) | size(WIDTH, EQUAL, 30),
    });
    
    if (state.focused){
        rowElement = rowElement | bgcolor(Color::Blue) | color(Color::Black) | bold;
    }
    
    return rowElement;
}


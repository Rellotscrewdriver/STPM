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
        rowElement = rowElement | bgcolor(Color::Blue) | color(Color::Black) | bold;
    }
    
    return rowElement;
}


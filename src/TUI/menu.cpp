#include "tui.h"

Component TUIFrontEnd::menu(){
    menu_option.entries_option.transform = [this](const EntryState& state) {
        return menuRowEntry(state);
    };

    //menu_option.on_enter = [&](){copyCreds();};

    updateMenuEnteries();

    return Menu(&menu_entries, &selected_row, menu_option);
}


Element TUIFrontEnd::menuRowEntry(const EntryState &state)
{
    if (state.index >= data.size()){
        return text("");
    }
    
    const auto& row = data[state.index];
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
    menu_entries.clear();
    for (size_t i = 0; i < data.size(); i++) {
        // Push empty strings; the text is handled by the transform function above
        menu_entries.push_back(""); 
    }
}
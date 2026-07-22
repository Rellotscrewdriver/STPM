#include "tui.h"

void TUIFrontEnd::copyCreds(){
    if (selected_row >= 0 && selected_row < data.size()) {
        std::string text_to_copy = data[selected_row].name;
    }    
}


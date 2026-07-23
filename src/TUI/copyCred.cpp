#include "tui.h"

void TUIFrontEnd::copyCreds(copyData type){
    if (selected_row >= 0 && selected_row < data.size()) {
        if(type == copyEmail){
            std::string text_to_copy = data[selected_row].name;
            //copyShit();
            status_message = "✅ Copied Email: \"" + text_to_copy + "\" to clipboard!";
        } else if(type == copySite){
            std::string text_to_copy = data[selected_row].role; // Copying the "Role" column
            //copyShit();

            status_message = "✅ Copied Link: \"" + text_to_copy + "\" to clipboard!";
        } else if(type == copyPass){
            std::string text_to_copy = data[selected_row].id;
            //copyShit();
            status_message = "✅ Copied Password: *********** to clipboard!";
        }

    }    
}




#include "dataManager.h"

void dataManager::copyCreds(copyData type, int selectedRow){
    if (selectedRow >= 0 && selectedRow < data.size()) {
        if(type == copyEmail){
            std::string text_to_copy = data[selectedRow].name;
            //copyShit();
            status_message = "✅ Copied Email: \"" + text_to_copy + "\" to clipboard!";
        } else if(type == copySite){
            std::string text_to_copy = data[selectedRow].role; // Copying the "Role" column
            //copyShit();

            status_message = "✅ Copied Link: \"" + text_to_copy + "\" to clipboard!";
        } else if(type == copyPass){
            std::string text_to_copy = data[selectedRow].id;
            //copyShit();
            status_message = "✅ Copied Password: *********** to clipboard!";
        }

    }    
}




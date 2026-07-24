#include "tui.h"

 
Component TUIFrontEnd::inputEmail(){
    input.transform = [this](InputState state) {
        return inputStyle(state);
    };

    return Input(&emailCred, "Enter your Email...", input);
}

Component TUIFrontEnd::inputSite(){
    input.transform = [this](InputState state) {
        return inputStyle(state);
    };

    return Input(&siteCred, "Enter the Link...", input);
}

Component TUIFrontEnd::inputMasterPass(){
    input.transform = [this](InputState state) {
        return inputStyle(state);
    };

    return Input(&siteCred, "Enter Master Password...", input);
}

Component TUIFrontEnd::inputEvent(){
    keyInputs input;
    return CatchEvent(menu(), [&](Event event) {
        if (show_dialog) return true; // Let the dialog handle events if it's open

        if (event == Event::Character(input.quitApp)) {
            screen.Exit();
            return true;
        }

        //Scrolling effect
        if (!data.empty()) {
            int max_index = static_cast<int>(data.size()) - 1;

            if ((event == input.altMoveUp || event == Event::Character(input.moveDown)) && selected_row == 0) {
                selected_row = max_index;
                return true;
            }

            // Loop Down: If at the last row and pressing Down or 'j', jump to the first row
            if ((event == input.altMoveUp || event == Event::Character(input.moveUp)) && selected_row == max_index) {
                selected_row = 0;
                return true;
            }
        }

        if (event == Event::Character(input.moveDown)) {
            return menu()->OnEvent(input.altMoveDown);
        }

        if (event == Event::Character(input.moveUp)) {
            return menu()->OnEvent(input.altMoveUp);
        }
        
        if (event == Event::Character(input.addDialog)) {
            addRow();
            activeLayer = addDialog;
            // dialog_container->TakeFocus();
            return true;
        }

        if (event == Event::Character(input.remDialog)) {
            deleteRow();
            activeLayer = remDialog;
            // dialog_container->TakeFocus();
            return true;
        }

        if (event == input.save) {
            saveData();
            return true;
        }

        //theme override
        if (event == Event::Character(input.themes)) {
            activeLayer = masterPass;
            dialogContainer()->TakeFocus();
            return true;
        }

        if (event == Event::Character(input.copyEmailKey)) {
            copyCreds(copyEmail);
            return true;
        }
    
        // Check if the user pressed 'r' or 'R' (for copying "Role")
        if (event == Event::Character(input.copySIteKey)) {
            copyCreds(copySite);
            return true;
        }

        if (event == Event::Character(input.copyPassKey)) {
            copyCreds(copyPass);
            return true;
        }

        if (event == input.edit) {
            emailCred = data[selected_row].name;
            siteCred = data[selected_row].role;
            activeLayer = editDialog;
            dialogContainer()->TakeFocus();
            return true;
        }
        return false;
    });
}

Component TUIFrontEnd::dialogInputEvent()
{
    return CatchEvent(dialogContainer(), [&](Event event) {
        if (event == Event::Escape) {
            activeLayer = mainMenu;
            return true; // Event handled
        }

        if (event == Event::ArrowDown) {
            if (dialog_selector < 2) {
                dialog_selector++;
                return true; // Consume the event
            }
            dialog_selector = 0; 
            return true;
        }
    
        if (event == Event::ArrowUp) {
            if (dialog_selector > 0) {
                dialog_selector--;
                return true; // Consume the event
            }
            dialog_selector = 2; 
            return true;
        }
        return false;
    });
}


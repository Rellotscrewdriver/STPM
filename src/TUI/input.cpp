#include "tui.h"


//TODO: make inputOption common 
Component TUIFrontEnd::inputEmail(){
    InputOption input;
    input.transform = [this](InputState state) {
        return inputStyle(state);
    };

    input.multiline = false;

    return Input(&emailCred, "Enter your Email...", input);
}

Component TUIFrontEnd::inputSite(){
    InputOption input;
    input.transform = [this](InputState state) {
        return inputStyle(state);
    };

    input.multiline = false;
    return Input(&siteCred, "Enter the Link...", input);
}

Component TUIFrontEnd::inputMasterPass(){
    InputOption input;
    input.transform = [this](InputState state) {
        return inputStyle(state);
    };

    input.multiline = false;
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

            if ((event == Event::ArrowUp || event == Event::Character('k')) && selected_row == 0) {
                selected_row = max_index;
                return true;
            }

            // Loop Down: If at the last row and pressing Down or 'j', jump to the first row
            if ((event == Event::ArrowDown || event == Event::Character('j')) && selected_row == max_index) {
                selected_row = 0;
                return true;
            }
        }

        if (event == Event::Character('j')) {
            return menu()->OnEvent(Event::ArrowDown);
        }

        if (event == Event::Character('k')) {
            return menu()->OnEvent(Event::ArrowUp);
        }
        
        if (event == Event::Character('n')) {
            addRow();
            activeLayer = addDialog;
            // active_layer = 1;
            // dialog_container->TakeFocus();
            return true;
        }

        if (event == Event::Character('d')) {
            deleteRow();
            activeLayer = remDialog;
            // active_layer = 1;
            // dialog_container->TakeFocus();
            return true;
        }

        if (event == Event::CtrlS) {
            saveData();
            return true;
        }

        //theme override
        if (event == Event::Character('a')) {
            activeLayer = masterPass;
            dialogContainer()->TakeFocus();
            return true;
        }

        if (event == Event::Character('c')) {
            if (selected_row >= 0 && selected_row < data.size()) {
                std::string text_to_copy = data[selected_row].name; // Copying the "Name" column
                //copy_to_clipboard(text_to_copy);
            
                status_message = "✅ Copied Name: \"" + text_to_copy + "\" to clipboard!";
                return true; // Stop event propagation
            }
        }
    
        // Check if the user pressed 'r' or 'R' (for copying "Role")
        if (event == Event::Character('v')) {
            if (selected_row >= 0 && selected_row < data.size()) {
                std::string text_to_copy = data[selected_row].role; // Copying the "Role" column
                //copy_to_clipboard(text_to_copy);

                status_message = "✅ Copied Role: \"" + text_to_copy + "\" to clipboard!";
                return true; // Stop event propagation
            }
        }

        if (event == Event::Return) {
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


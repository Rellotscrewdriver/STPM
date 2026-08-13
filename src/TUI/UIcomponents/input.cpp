#include "../tui.h"

 
void TUIFrontEnd::inputEmail(){
    input.transform = [this](InputState state) {
        return inputStyle(state);
    };

    emailInput = Input(&emailCred, "Enter your Email...", input);
}

void TUIFrontEnd::inputSite(){
    input.transform = [this](InputState state) {
        return inputStyle(state);
    };

    siteInput = Input(&siteCred, "Enter the Link...", input);
}

void TUIFrontEnd::inputMasterPass(){
    input.transform = [this](InputState state) {
        return inputStyle(state);
    };

    masterPassword = Input(&siteCred, "Enter Master Password...", input);
}

Component TUIFrontEnd::inputEvent(){

    return CatchEvent(menuComponent, [&](Event event) {
        if (show_dialog) return true; // Let the dialog handle events if it's open

        if (event == Event::Character('q')) {
            screen.Exit();
            return true;
        }

        //Scrolling effect
        if (!db.data.empty()) {
            int max_index = static_cast<int>(db.data.size()) - 1;

            if ((event == Event::Character('k') || event == Event::ArrowUp) && selected_row == 0) {
                selected_row = max_index;
                return true;
            }

            // Loop Down: If at the last row and pressing Down or 'j', jump to the first row
            if ((event == Event::Character('j') || event == Event::ArrowDown) && selected_row == max_index) {
                selected_row = 0;
                return true;
            }
        }

        if (event == Event::Character('j')) {
            return menuComponent->OnEvent(Event::ArrowDown);
        }

        if (event == Event::Character('k')) {
            return menuComponent->OnEvent(Event::ArrowUp);
        }
        
        if (event == Event::Character('n')) {
            db.addRow();
            //activeLayer = addDialog;
            // dialog_container->TakeFocus();
            return true;
        }

        if (event == Event::Character('d')) {
            db.deleteRow(selected_row);
            //activeLayer = remDialog;
            // dialog_container->TakeFocus();
            return true;
        }

        if (event == Event::CtrlS) {
            db.saveData();
            return true;
        }

        //theme override
        if (event == Event::Character('p')) {
            activeLayer = masterPass;
            dialogContainer()->TakeFocus();
            return true;
        }

        if (event == Event::Character('c')) {
            db.copyCreds(dataManager::copyEmail, selected_row);
            return true;
        }
    
        // Check if the user pressed 'r' or 'R' (for copying "Role")
        if (event == Event::Character('v')) {
            db.copyCreds(dataManager::copySite, selected_row);
            return true;
        }

        if (event == Event::Character('b')) {
            db.copyCreds(dataManager::copyPass, selected_row);
            return true;
        }

        if (event == Event::Return) {
            emailCred = db.data[selected_row].name;
            siteCred = db.data[selected_row].role;
            activeLayer = editDialog;
            dialogContainer()->TakeFocus();
            return true;
        }
        return false;
    });
}

Component TUIFrontEnd::dialogInputEvent()
{
    return CatchEvent(dContainer, [&](Event event) {
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


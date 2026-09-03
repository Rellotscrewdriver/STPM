#include "../tui.h"


void TUIFrontEnd::inputEmail(){
    emailInput = Input(&emailCred, "Enter your Email...", input);
}

void TUIFrontEnd::inputSite(){
    siteInput = Input(&siteCred, "Enter the Link...", input);
}

void TUIFrontEnd::inputMasterPass(){
    masterPassword = Input(&siteCred, "Enter Master Password...", input);
}

Component TUIFrontEnd::inputEvent(){

    return CatchEvent(menuComponent, [&](Event event) {
        if (layerNo != 0) return false;

        if (event == Event::Character('q') || event == Event::Escape) {
            db.saveData();
            db.status_message = "Saved this stupid Data!";
            screen.Exit();
            return true;
        }

        if (event == Event::Character('d')) {
            activeLayer = remDialog;
            switchDialog(remDialog);
            isDataEmpty = false;
                        
            dContainer->TakeFocus();
            return true;
        }

        if (event == Event::Character('n')) {
            activeLayer = addDialog;

            switchDialog(addDialog);
            passCred = gp.getgeneratedPass();
            emailCred = "";
            siteCred = "";

            dContainer->TakeFocus();
            //activeLayer = addDialog;
            // dialog_container->TakeFocus();
            return true;
        }

        //Scrolling effect(BROKEN BUT CAN'T BE FIXED)
        if (!siteDataNew.empty()) {
            int max_index = static_cast<int>(siteDataNew.size()) - 1;

            if ((event == Event::Character('k') || event == Event::ArrowUp) && selected_row <= 0) {
                selected_row = max_index;
                return true;
            }

            // Loop Down: If at the last row and pressing Down or 'j', jump to the first row
            if ((event == Event::Character('j') || event == Event::ArrowDown) && selected_row >= max_index) {
                selected_row = 0;
                return true;
            }

        }

        //TODO: this might give me problems later
        if (event == Event::CtrlS) {
            db.saveData();
            db.status_message = "Saved this stupid Data!";
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
            activeLayer = editDialog;
            switchDialog(editDialog);
            passCred = siteDataNew[selected_row].getPass();
            emailCred = siteDataNew[selected_row].getEmail();
            siteCred = siteDataNew[selected_row].getLink();
            dContainer->TakeFocus();
            return true;
        }
        return false;
    });
}

Component TUIFrontEnd::dialogInputEvent(){
    return CatchEvent(dContainer, [&](Event event) {
        if (event == Event::Escape) {
            if(activeLayer == newUserD || activeLayer == masterPassD){
                screen.Exit();
                return true;
            }
            activeLayer = mainMenu;
            dialogSelector = 0;
            layerNo = 0;
            return true; // Event handled
        }

        if (event == Event::ArrowDown) {
            if (dialogSelector <= maxDialogSelections) {
                dialogSelector++;
                return true; // Consume the event
            }
            dialogSelector = 1; 
            return true;
        }
    
        if (event == Event::ArrowUp) {
            if (dialogSelector >= 1) {
                dialogSelector--;
                return true; // Consume the event
            }
            dialogSelector = maxDialogSelections; 
            return true;
        }
        return false;
    });
}


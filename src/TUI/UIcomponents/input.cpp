#include "../tui.h"

Component TUIFrontEnd::inputEvent(){

    return CatchEvent(menuComponent, [&](Event event) {
        if (layerNo != 0) return false;

        if (event == Event::Character('q') || event == Event::Escape) {
            db.saveData();
            db.statusMessage = "Saved the Data!";
            screen.Exit();
            return true;
        }

        if (event == Event::Character('d') && !siteDataNew.empty()) {
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
            return true;
        }

        //Scrolling effect(BROKEN BUT CAN'T BE FIXED)
        if (!siteDataNew.empty()) {
            int max_index = static_cast<int>(siteDataNew.size() - 1);

            if ((event == Event::Character('k') || event == Event::ArrowUp) && selectedRow <= 0) {
                selectedRow = max_index;
                return true;
            }

            // Loop Down: If at the last row and pressing Down or 'j', jump to the first row
            if ((event == Event::Character('j') || event == Event::ArrowDown) && selectedRow >= max_index) {
                selectedRow = 0;
                return true;
            }

        }
        
        if (event == Event::CtrlS) {
            db.saveData();
            db.statusMessage = "Saved the Data!";
            return true;
            db.statusMessage = "nothing was copied to clipboard";            
        }

        if (event == Event::Character('c')) {
            db.copyCreds(dataManager::copyEmail, selectedRow);
            return true;
        }
    
        if (event == Event::Character('v')) {
            db.copyCreds(dataManager::copySite, selectedRow);
            return true;
        }

        if (event == Event::Character('b')) {
            db.copyCreds(dataManager::copyPass, selectedRow);
            return true;
        }

        if (event == Event::Return) {
            activeLayer = editDialog;
            switchDialog(editDialog);
            passCred = siteDataNew[selectedRow].getPass();
            emailCred = siteDataNew[selectedRow].getEmail();
            siteCred = siteDataNew[selectedRow].getLink();
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
            if (dialogSelector <= maxDialogSelect) {
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
            dialogSelector = maxDialogSelect; 
            return true;
        }
        return false;
    });
}


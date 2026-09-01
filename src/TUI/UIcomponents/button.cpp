#include "../tui.h"

Component TUIFrontEnd::saveButton(){
    return Button("Save", [&] {
        if (!validateInputs(emailCred, siteCred)) {
            isValidCredentials = "Email or Site is invaild";
            return; // Prevents adding invalid data
        }

        siteDataNew[selected_row].getEmail() = emailCred;
        siteDataNew[selected_row].getLink() = siteCred;
        db.updateMenuEnteries();
        layerNo = 0;
        activeLayer = mainMenu;
    }, saveOption); 
}

Component TUIFrontEnd::confirmButton(){
    return Button("Yes", [&] {
        if (siteDataNew.empty()) {
            isDataEmpty = true;
            selected_row = 0;
            return;
        } else if (selected_row >= static_cast<int>(siteDataNew.size())) {
            selected_row = static_cast<int>(siteDataNew.size()) - 1;
        }

        db.deleteRow(selected_row);

        layerNo = 0;
        activeLayer = mainMenu;
        db.updateMenuEnteries();            
    }, saveOption); 
}

Component TUIFrontEnd::addButton(){
    return Button("Add", [&] {
        if (!validateInputs(emailCred, siteCred)) {
            isValidCredentials = "Email or Site is invaild";
            return; // Prevent adding invalid data
        }

        db.addRow(emailCred, siteCred, passCred);
        layerNo = 0;
        activeLayer = mainMenu;
        db.updateMenuEnteries();
        return;
    }, saveOption); 
}


Component TUIFrontEnd::cancelButton(){
    return Button("Cancel", [&] { 
        activeLayer = mainMenu;
        layerNo = 0; 
    }, cancelOption);
}

Component TUIFrontEnd::noButton(){
    return Button("No", [&] { 
        activeLayer = mainMenu;
        layerNo = 0; 
    }, cancelOption);
}


Component TUIFrontEnd::genPassButton(){
    return Button("", [&] { 
        if(activeLayer == addDialog){
            passCred = gp.getgeneratedPass();
        } else {
            siteDataNew[selected_row].getPass() = gp.getgeneratedPass();
        }
    }, cancelOption);
}

Component TUIFrontEnd::editBtnLayout(){
    return ftxui::Container::Horizontal({
        saveBtn, 
        cancelBtn
    }, &dialogBtnsSelector);
}

Component TUIFrontEnd::addBtnLayout(){
    return ftxui::Container::Horizontal({
        addBtn, 
        cancelBtn
    }, &dialogBtnsSelector);
}

Component TUIFrontEnd::remBtnLayout(){
    return ftxui::Container::Horizontal({
        yesBtn, 
        noBtn
    }, &dialogBtnsSelector);
}

Component TUIFrontEnd::passBtnLayout() {
    return ftxui::Container::Horizontal({
        checkBtn, 
        exitBtn
    }, &dialogBtnsSelector);    
}

Component TUIFrontEnd::checkButton() {
    return Button("Check", [&] {
        // if (!validateInputs(emailCred, siteCred)) {
        //     isValidCredentials = "Email or Site is invaild";
        //     return; // Prevent adding invalid data
        // }

        // db.addRow(emailCred, siteCred, passCred);
        layerNo = 0;
        activeLayer = mainMenu;
        db.updateMenuEnteries();
        return;
    }, saveOption);
}

Component TUIFrontEnd::exitButton() {
    return Button("EXIT", [&] { 
        screen.Exit();
    }, cancelOption);
}
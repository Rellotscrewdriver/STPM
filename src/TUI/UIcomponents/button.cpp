#include "../tui.h"

Component TUIFrontEnd::saveButton(){
    return Button("Save", [&] {
        if (!validateInputs(emailCred, siteCred)) {
            isValidCredentials = "Email or Site is invaild";
            return;
        }

        siteDataNew[selectedRow].getEmail() = emailCred;
        siteDataNew[selectedRow].getLink() = siteCred;
        db.updateMenuEnteries();
        layerNo = 0;
        activeLayer = mainMenu;
    }, saveOption); 
}

Component TUIFrontEnd::confirmButton(){
    return Button("Yes", [&] {
        if (siteDataNew.empty()) {
            isDataEmpty = true;
            selectedRow = 0;
            return;
        }

        db.deleteRow(selectedRow);

        layerNo = 0;
        activeLayer = mainMenu;
        db.updateMenuEnteries();            
    }, saveOption); 
}

Component TUIFrontEnd::addButton(){
    return Button("Add", [&] {
        if (!validateInputs(emailCred, siteCred)) {
            isValidCredentials = "Email or Site is invaild";
            return;
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
    #if defined(_WIN32) || defined(__APPLE__)
        ftxui::ConstStringRef txtNameTemp = "ReP";
    #else
        ftxui::ConstStringRef txtNameTemp = "";
    #endif
    
    return Button(txtNameTemp, [&] { 
        if(activeLayer == addDialog){
            passCred = gp.getgeneratedPass();
        } else {
            siteDataNew[selectedRow].getPass() = gp.getgeneratedPass();
        }
    }, genPassOption);
}


Component TUIFrontEnd::editBtnLayout()
{
    return ftxui::Container::Horizontal({
        saveBtn, 
        cancelBtn
    }, &dialogBtnsNavi);
}

Component TUIFrontEnd::addBtnLayout(){
    return ftxui::Container::Horizontal({
        addBtn, 
        cancelBtn
    }, &dialogBtnsNavi);
}

Component TUIFrontEnd::remBtnLayout(){
    return ftxui::Container::Horizontal({
        yesBtn, 
        noBtn
    }, &dialogBtnsNavi);
}

Component TUIFrontEnd::passBtnLayout() {
    return ftxui::Container::Horizontal({
        checkBtn, 
        exitBtn
    }, &dialogBtnsNavi);    
}

Component TUIFrontEnd::checkButton() {
    return Button("Verify", [&] {
        masterPassCheck();
    }, verifyOption);
}

void TUIFrontEnd::masterPassCheck(){
    if(activeLayer == masterPassD){
        if (!validateMasterPass()) {
            isValidPassword = false;
            return; // Prevent adding invalid data
        }
    } else if(activeLayer == newUserD){
        if(!validateNewMasterPass()){
            isValidPassword = false;
            return; // Prevent adding invalid data
        }
    }
    db.loadData();
    layerNo = 0;
    activeLayer = mainMenu;
    db.updateMenuEnteries();
    return;
}

Component TUIFrontEnd::exitButton() {
    return Button("Quit", [&] { 
        screen.Exit();
    }, cancelOption);
}
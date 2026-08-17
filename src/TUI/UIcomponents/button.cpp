#include "../tui.h"
#include "../genPass/genPass.h"

Component TUIFrontEnd::saveButton(){
    return Button("Save", [&] {
        db.data[selected_row].name = emailCred;
        db.data[selected_row].role = siteCred;
        db.updateMenuEnteries();
        layerNo = 0;
        activeLayer = mainMenu;
    }, saveOption); 
}

Component TUIFrontEnd::confirmButton(){
    return Button("Yes", [&] {
        db.deleteRow(selected_row);
        layerNo = 0;
        activeLayer = mainMenu;
        db.updateMenuEnteries();            
    }, saveOption); 
}

Component TUIFrontEnd::addButton(){
    return Button("Add", [&] {
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

Component TUIFrontEnd::genPassButton(){
    return Button("", [&] { 
        //resetPassword()
        GeneratePass ps;
        if(activeLayer == addDialog){
            passCred = ps.getgeneratedPass();
        } else {
            db.data[selected_row].id = ps.getgeneratedPass();
        }
    }, cancelOption);
}

Component TUIFrontEnd::editBtnLayout(){
    return ftxui::Container::Horizontal({
        saveBtn, 
        cancelBtn
    });
}

Component TUIFrontEnd::addBtnLayout(){
    return ftxui::Container::Horizontal({
        addBtn, 
        cancelBtn
    });
}

Component TUIFrontEnd::remBtnLayout(){
    return ftxui::Container::Horizontal({
        yesBtn, 
        cancelBtn
    });
}

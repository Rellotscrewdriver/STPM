#include "../tui.h"
#include "../genPass/genPass.h"

Component TUIFrontEnd::saveButton(){
    //save_option = saveBtnStyle();
    return Button("Save", [&] {
        if(activeLayer == addDialog){
            db.addRow();
            layerNo = 0;
            activeLayer = mainMenu;
            db.updateMenuEnteries();
            return;
        }

        if(activeLayer == remDialog){
            db.deleteRow(selected_row);
            layerNo = 0;
            activeLayer = mainMenu;
            db.updateMenuEnteries();            
            return;
        }

        db.data[selected_row].name = emailCred;
        db.data[selected_row].role = siteCred;
        db.updateMenuEnteries();
        layerNo = 0;
        activeLayer = mainMenu;
    }, saveOption); 
}

Component TUIFrontEnd::cancelButton(){
    return Button("Cancel", [&] { 
        activeLayer = mainMenu;
        layerNo = 0; 
    }, cancelOption);
}

Component TUIFrontEnd::genPassButton(){
    return Button(" ", [&] { 
        //resetPassword()
        GeneratePass ps;
        db.data[selected_row].id = ps.getgeneratedPass();
    }, cancelOption);
}


Component TUIFrontEnd::btnLayout(){
    return ftxui::Container::Horizontal({
        saveBtn, 
        cancelBtn
    });
}
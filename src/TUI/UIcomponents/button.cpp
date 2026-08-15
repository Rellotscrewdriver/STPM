#include "../tui.h"


Component TUIFrontEnd::saveButton(){
    //save_option = saveBtnStyle();
    return Button("Save", [&] {
        db.data[selected_row].name = emailCred;
        db.data[selected_row].role = siteCred;
        updateMenuEnteries();
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
    return Button("", [&] { 
        //resetPassword()
        db.data[selected_row].id = "meow";
    }, cancelOption);
}


Component TUIFrontEnd::btnLayout(){
    return ftxui::Container::Horizontal({
        saveBtn, 
        cancelBtn
    });
}


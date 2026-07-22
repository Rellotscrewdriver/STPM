#include "tui.h"

Component TUIFrontEnd::btnLayout(){
    return ftxui::Container::Horizontal({
        saveBtn(), 
        cancelBtn()
    });
}

//TODO: make inputOption common
Component TUIFrontEnd::saveBtn(){
    ButtonOption save_option;
    save_option.transform = [this](const EntryState& state) {
        return saveBtnStyle(state);
    };

    return Button("Save", [&] {
        data[selected_row].name = emailCred;
        data[selected_row].role = siteCred;
        updateMenuEnteries();
        activeLayer = mainMenu;
    }, save_option);
}

Component TUIFrontEnd::cancelBtn(){
    ButtonOption cancel_option;
    cancel_option.transform = [this](const EntryState& state) {
        return cancelBtnStyle(state);
    };

    return Button("Cancel", [&] {
        activeLayer = mainMenu;
    }, cancel_option);;
}

Component TUIFrontEnd::genPassBtn(){
    ButtonOption save_option;
    save_option.transform = [this](const EntryState& state) {
        return saveBtnStyle(state);
    };

    return Button("󰜉", [&] {
        //generatePass
        
    }, save_option);
}

Component TUIFrontEnd::confrimPassBtn(){
    ButtonOption save_option;
    save_option.transform = [this](const EntryState& state) {
        return saveBtnStyle(state);
    };

    return Button("Confirm", [&] {
        //check password() here
        activeLayer = mainMenu;
    }, save_option);
}

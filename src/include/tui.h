#pragma once

#include "includes.h"
#include "siteObj.h"
#include <FTXUI/include/ftxui/ftxui.hpp>

using namespace ftxui;

struct Record {
    std::string id;
    std::string name;
    std::string role;
};

class TUIFrontEnd {
public:
    TUIFrontEnd();
    void exec();

private:
    struct keyInputs {
        char editDialog = 'e';
        char quitApp = 'q';
        //char 
    }

    enum layers {
        mainMenu,
        editDialog,
        addDialog,
        remDialog,
        masterPass
    };

    enum copyData {

    };

    std::string status_message = "nothing was copied to clipboard";
    std::string copyIns = "Use Arrows to navigate | Press 'c' to copy Name | Press 'v' to copy Role";
    
    //terminal window size
    const int minHeight = 11;
    const int minWidth = 55;
    
    //UI variables and states
    int selected_row = 0;
    std::string copyCred;
    std::vector<Record> data;
    std::vector<std::string> menu_entries;
    layers activeLayer;
    int dialog_selector = 0;
    bool show_dialog = false;

    std::string emailCred;
    std::string siteCred;


    /*
        TODO: on friday, separate these into classes
        TUIFrontend -> userInputs
                    -> buttons
                    -> operations
                    -> title and header
                    -> version
                    -> style
    */
    Component renderer;
    ScreenInteractive screen = ScreenInteractive::Fullscreen();
    Component layoutManager();
    Element buildMainLayout();
    void renderLayout();

    //User Input
    Component inputEmail();
    Component inputSite();
    Component inputMasterPass();

    //Input Events
    Component inputEvent();
    Component dialogInputEvent();

    //buttons
    Component saveBtn();
    Component cancelBtn();
    Component genPassBtn();
    Component confrimPassBtn();

    //operations
    void addRow();
    void deleteRow();
    void saveData();

    //Style
    Component btnLayout();
    Element saveBtnStyle(const EntryState &state);
    Element cancelBtnStyle(const EntryState &state);
    Element inputStyle(InputState state);


    //title and header
    Element title();
    Element tableHeader();

    //dialog
    Component dialogContainer();
    Element editPopup();
    Element addPopup();
    Element remPopup();
    Element passPopup();


    //instructions
    Element warningWindow(Dimensions size);

    Element menuRowEntry(const EntryState& state);
    void copyCreds();
    Component menu();
    void updateMenuEnteries();
    MenuOption menu_option;

};
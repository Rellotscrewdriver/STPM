#pragma once

#include "includes.h"
#include "siteObj.h"
#include "dataManager/dataManager.h"
#include <FTXUI/include/ftxui/ftxui.hpp>

using namespace ftxui;

class TUIFrontEnd {
public:
    TUIFrontEnd();
    void exec();

private:

    void initComponents();


    dataManager db;
    
    enum layers {
        mainMenu,
        editDialog,
        addDialog,
        remDialog,
        masterPass
    };



    
    //terminal window size
    const int minHeight = 11;
    const int minWidth = 55;
    
    //UI variables and states
    int selected_row = 0;
    std::string copyCred;

    layers activeLayer;
    int layerNo = 0;
    int dialog_selector = 0;
    bool show_dialog = false;

    std::string emailCred;
    std::string siteCred;


    /*
        TODO: on friday, separate these into classes
        
        TUIFrontend -> style -> userInputs
                             -> buttons
                             -> title and header
                    -> dialog
                    -> instruction manual
                    -> operations
                    -> version
    */
    Component renderer;
    ScreenInteractive screen = ScreenInteractive::Fullscreen();
    Component layoutManager();
    Element buildMainLayout();
    void renderLayout();

    //User Input
    void inputEmail();
    void inputSite();
    void inputMasterPass();

    //Input Events
    Component inputEvent();
    Component dialogInputEvent();

    //operations


    //Style
    InputOption input;
    ButtonOption confirmBtn;
    ButtonOption save_option;
    ButtonOption cancel_option;
    ButtonOption resetPass;
    Component btnLayout();
    Element saveBtnStyle(const EntryState &state);
    Element cancelBtnStyle(const EntryState &state);
    Element inputStyle(InputState state);

    //meow
    Component emailInput;
    Component siteInput;
    Component masterPassword;
    Component menuComponent;
    Component saveBtn;
    Component cancelBtn;
    Component genPassBtn;
    Component dContainer;
    Component mainInputEvent;
    Component dInputEvent;


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
    
    void updateMenuEnteries();
    MenuOption menu_option;
};
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
    void applyStyle();

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

    layers activeLayer = mainMenu;
    int layerNo = 0;
    int dialogSelector = 0;
    int dialogBtnsSelector = 0;
    int maxDialogSelections = 12;

    std::string emailCred;
    std::string siteCred;
    std::string passCred;

    Component renderer;
    ScreenInteractive screen = ScreenInteractive::Fullscreen();
    Component layoutManager();
    Element buildMainLayout();
    void renderLayout();

    //String Validation
    std::string emailErrorMsg;
    std::string siteErrorMsg;
    bool isEmailValid = true;
    bool isSiteValid = true;
    bool validateEmail(const std::string& email);
    bool validateSite(const std::string& site);


    //User Input
    void inputEmail();
    void inputSite();
    void inputMasterPass();

    //Input Events
    Component inputEvent();
    Component dialogInputEvent();

    //Buttons
    Component saveButton();
    Component confirmButton();
    Component addButton();
    Component cancelButton();
    Component noButton();
    Component genPassButton();
    Component editBtnLayout();
    Component addBtnLayout();
    Component remBtnLayout();

    //Style
    InputOption input;
    ButtonOption confirmBtn;
    ButtonOption saveOption;
    ButtonOption cancelOption;
    ButtonOption resetPass;
    Element saveBtnStyle(const EntryState &state);
    Element cancelBtnStyle(const EntryState &state);
    Element inputStyle(InputState state);

    //meow
    Component emailInput;
    Component siteInput;
    Component masterPassword;
    Component menuComponent;
    Component btnContainer;
    Component saveBtn;
    Component yesBtn;
    Component noBtn;
    Component addBtn;

    Component cancelBtn;
    
    Component genPassBtn;
    Component dContainer;
    Component mainInputEvent;
    Component dInputEvent;

    //title and header
    Element title();
    Element tableHeader();

    //instructions
    Element warningWindow(Dimensions size);

    //actual dialogs
    void switchDialog(layers dialogLayer);
    Element editPopup();
    Element addPopup();
    Element remPopup();
    Element passPopup();

    Element menuRowEntry(const EntryState& state);
    
    void updateMenuEnteries();
    
    MenuOption menu_option;
};
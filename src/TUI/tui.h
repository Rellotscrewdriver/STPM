#pragma once

#include "includes.h"
#include "siteObj.h"
#include "dataManager/dataManager.h"
#include "../genPass/genPass.h"
#include <FTXUI/include/ftxui/ftxui.hpp>

using namespace ftxui;

class TUIFrontEnd {
public:
    TUIFrontEnd();
    void exec();

private:
    enum layers {
        mainMenu,
        editDialog,
        addDialog,
        remDialog,
        masterPassD,
        newUserD
    };

    
    //dependencies from other classes
    dataManager db;
    GeneratePass gp;


    //terminal window size
    const int minHeight = 11;
    const int minWidth = 72;


    //initialization
    void firstTimeSetup();
    void initComponents();
    void applyStyle();
    void initOther();
    void initButtons();
    void initInputs();    
        

    //UI variables and states
    layers activeLayer = mainMenu;
    int layerNo = 0;
    int dialogSelector = 0;
    int dialogBtnsNavi = 0;
    int maxDialogSelect = 12;
    int selectedRow = 0;


    // Credential Strings
    std::string copyCred;    
    std::string emailCred;
    std::string siteCred;
    std::string passCred;
    std::string masterPassT;
    std::string masterPassTDup;

    
    // Validation States & Messages
    bool isValidCredentials = true;
    bool isValidPassword = false;
    bool isDataEmpty = false;
    std::string validationMsg;
    std::string passMsg;

    //Validation Methods
    bool validateInputs(const std::string& email, const std::string& site);
    bool validateNewMasterPass();
    bool validateMasterPass();


    // FTXUI Base Components & Interactive Screen
    ScreenInteractive screen = ScreenInteractive::Fullscreen();
    Component renderer;


    //layout renderers
    Component layoutManager();
    Element buildMainLayout();
    void renderLayout();


    //Style
    InputOption input;
    InputOption mInput;
    ButtonOption confirmBtn;
    ButtonOption saveOption;
    ButtonOption cancelOption;
    ButtonOption genPassOption;  
    ButtonOption verifyOption;
    ButtonOption resetPass;
    MenuOption menuOption;

    //Element Style functions
    Element inputEleStyle(
        InputState state, 
        Color focusBg, Color focusFg, 
        Color idleBg, Color idleFg
    );

    Element buttonEleStyle(
        const EntryState &state, 
        Color focusBg, Color focusFg, 
        Color activeBg, Color activeFg,
        Color idleBg, Color idleFg
    );

    Element saveBtnStyle(const EntryState &state);
    Element cancelBtnStyle(const EntryState &state);
    Element genPassBtnStyle(const EntryState &state);
    Element verifyBtnStyle(const EntryState &state);    
    Element inputStyle(InputState state);
    Element inputMasterStyle(InputState state);


    // Input Element
    Component emailInput;
    Component siteInput;
    Component passInput;
    Component passInputDup;


    //Window Containers
    Component menuComponent;
    Component btnContainer;
    Component dContainer;    


    // Buttons Components & functions
    Component saveBtn;
    Component yesBtn;
    Component addBtn;
    Component checkBtn;
    Component exitBtn;
    Component noBtn;
    Component cancelBtn;
    Component genPassBtn;

    Component saveButton();
    Component confirmButton();
    Component addButton();
    Component checkButton();
    Component exitButton();
    Component cancelButton();
    Component noButton();
    Component genPassButton();

    void masterPassCheck();

    // Button layouts
    Component editBtnLayout();
    Component addBtnLayout();
    Component remBtnLayout();
    Component passBtnLayout();


    //Keyboard Input Events
    Component mainInputEvent;
    Component dInputEvent;

    //Input Catchers
    Component inputEvent();
    Component dialogInputEvent();


    //title and headers
    Element title();
    Element tableHeader();
    Element warningWindow(Dimensions size);


    //dialog renderers
    void switchDialog(layers dialogLayer);
    Element editPopup();
    Element addPopup();
    Element remPopup();
    Element newUser();
    Element masterPass();


    //main menu
    Element menuRowEntry(const EntryState& state);
};
#pragma once

#include "includes.h"
#include "siteObj.h"
#include "dataManager/dataManager.h"
#include "../genPass/genPass.h"
#include <FTXUI/include/ftxui/ftxui.hpp>

using namespace ftxui;

/**
 * a TUI Frontend for STPM
 */
class TUIFrontEnd {
public:
    /**
     * this constructor initalizes all the elements of the app
     */
    TUIFrontEnd();

    /**
     * execute the TUI app
     */
    void exec();

private:
    
    /**
     * mainly used to switch between different states
     */
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


    //minimum terminal window size
    const int minHeight = 11;
    const int minWidth = 72;


    //initialization
    /**
     * checks whether creden.mypass file is empty or exists
     */
    void firstTimeSetup();

    /**
     * warpper member to initialize components at the start 
     * since FTXUI doesn't allow element or component creation after calling run()
     */
    void initComponents();
    
    /**
     * apply styles to components
     */
    void applyStyle();
    
    /**
     * initialize misc. components
     */
    void initOther();
    
    /**
     * initialize button components
     */
    void initButtons();
    
    /**
     * initialize input components
     */
    void initInputs();    
        

    //UI variables and states
    /**
     * sets the active state of TUI session
     */
    layers activeLayer = mainMenu;

    /**
     * setting layer between main menu and dialog state, since Container::Tab takes only int, enums are prohibited
     */
    int layerNo = 0;

    /**
     * navigate between elements or components in a dialog
     */
    int dialogSelector = 0;

    /**
     * navigate between buttons in a dialog
     */    
    int dialogBtnsNavi = 0;

    /**
     * limit between elements or components in a dialog
     */
    int maxDialogSelect = 12;

    /**
     * a row that is in active state
     */
    int selectedRow = 0;


    // Credential Strings
    /**
     * used in FTXUI::Input() to store the string
     */
    std::string emailCred;

    /**
     * used in FTXUI::Input() to store the string
     */
    std::string siteCred;

    /**
     * used in FTXUI::Input() to store the string
     */
    std::string passCred;

    /**
     * used in FTXUI::Input() to store the string
     */
    std::string masterPassT;

    /**
     * used in FTXUI::Input() to store the string
     */
    std::string masterPassTDup;

    
    // Validation States & Messages
    /**
     * used to display error message when either email or link is invalid
     */
    bool isValidCredentials = true;
  
    /**
     * used to display error message when master password is invalid
     */
    bool isValidPassword = false;
   
    /**
     * used to display error message when deleting a void entry
     */
    bool isDataEmpty = false;
    
    /**
     * display what error message
     */
    std::string validationMsg;
    
    /**
     * display what error message
     */
    std::string passMsg;

    //Validation Methods
    /**
     * checks whether the inputs are valid or not by using regex pattern from re2
     * 
     * @param email
     * @param site
     * @returns true only if both match the respective pattern
     */    
    bool validateInputs(const std::string& email, const std::string& site);

    /**
     * checks whether the inputs are valid and generate the hash 
     * 
     * @returns true only if both match
     */    
    bool validateNewMasterPass();

    /**
     * checks whether the master password input is valid 
     * 
     * @returns true only if the hash has been successfully verified
     */    
    bool validateMasterPass();


    // FTXUI Base Components & Interactive Screen
    /**
     * controls what type of window it displays 
     */
    ScreenInteractive screen = ScreenInteractive::Fullscreen();

    /**
     * controls what layout it needs to show 
     */
    Component renderer;


    //layout renderers
    /**
     * manages the type of layout using layerNo variable
     */
    Component layoutManager();
    /**
     * sets the layout of main menu
     */
    Element buildMainLayout();
    /**
     * renders the layout by the renderer component
     */
    void renderLayout();


    //Style
    /**
     * style option for most inputs
     */
    InputOption input;
    
    /**
     * style option for master password inputs
     */
    InputOption mInput;
    
    /**
     * style option for confirm button
     */
    ButtonOption confirmBtn;
    
    /**
     * style option for save button
     */
    ButtonOption saveOption;
    
    /**
     * style option for cancel button
     */
    ButtonOption cancelOption;
    
    /**
     * style option for generate Password button
     */    
    ButtonOption genPassOption;  
    
    /**
     * style option for verify button
     */
    ButtonOption verifyOption;

    /**
     * style option for the menu
     */    
    MenuOption menuOption;

    //Element Style functions
    /**
     * style member function for button in different states 
     */
    Element inputEleStyle(
        InputState state, 
        Color focusBg, Color focusFg, 
        Color idleBg, Color idleFg
    );

    /**
     * style member function for input in different states 
     */
    Element buttonEleStyle(
        const EntryState &state, 
        Color focusBg, Color focusFg, 
        Color activeBg, Color activeFg,
        Color idleBg, Color idleFg
    );

    /**
     * style member for save button
     */
    Element saveBtnStyle(const EntryState &state);
    
    /**
     * style member for cancel button
     */
    Element cancelBtnStyle(const EntryState &state);

    /**
     * style member for generate Password button
     */    
    Element genPassBtnStyle(const EntryState &state);

    /**
     * style member for verify button
     */
    Element verifyBtnStyle(const EntryState &state);    

    /**
     * style member for input button
     */
    Element inputStyle(InputState state);
    
    /**
     * style member for master password input button
     */    
    Element inputMasterStyle(InputState state);


    // Input Element
    /**
     * Input component for email entry
     */
    Component emailInput;
    
    /**
     * Input component for site entry
     */
    Component siteInput;
    
    /**
     * Input component for master password entry
     */
    Component passInput;

    /**
     * Input component for duplicate master password entry
     */
    Component passInputDup;


    //Window Containers
    /**
     * menu component container
     */    
    Component menuComponent;
    /**
     * button row component container
     */    
    Component btnContainer;
    /**
     * dialog component container
     */    
    Component dContainer;    


    // Buttons Components & functions
    /**
     * Button component for save button
     */
    Component saveBtn;

    /**
     * Button component for yes button
     */
    Component yesBtn;

    /**
     * Button component for add button
     */
    Component addBtn;

    /**
     * Button component for check button
     */
    Component checkBtn;

    /**
     * Button component for exit button
     */
    Component exitBtn;

    /**
     * Button component for no button
     */
    Component noBtn;

    /**
     * Button component for cancel button
     */
    Component cancelBtn;

    /**
     * Button component for generate password button
     */
    Component genPassBtn;

    /**
     * Button member function used to initalize the component for persistence
     */    
    Component saveButton();

    /**
     * Button member function used to initalize the component for persistence
     */    
    Component confirmButton();

    /**
     * Button member function used to initalize the component for persistence
     */    
    Component addButton();

    /**
     * Button member function used to initalize the component for persistence
     */    
    Component checkButton();

    /**
     * Button member function used to initalize the component for persistence
     */    
    Component exitButton();

    /**
     * Button member function used to initalize the component for persistence
     */    
    Component cancelButton();

    /**
     * Button member function used to initalize the component for persistence
     */    
    Component noButton();

    /**
     * Button member function used to initalize the component for persistence
     */    
    Component genPassButton();

    /**
     * determines the type of user(old or new) and once verified with success it switches to main menu 
     * this is used in mInput(on pressing enter key) and verify button
     */
    void masterPassCheck();

    // Button layouts
    /**
     * Edit Button Layout
     */
    Component editBtnLayout();

    /**
     * Add Button Layout
     */
    Component addBtnLayout();

    /**
     * Remove Button Layout
     */
    Component remBtnLayout();

    /**
     * Master Password Button Layout
     */
    Component passBtnLayout();


    //Keyboard Input Events
    /**
     * Keyboard Input Event Component in main menu
     */
    Component mainInputEvent;

    /**
     * Keyboard Input Event Component in dialogs
     */
    Component dInputEvent;

    //Input Catchers
    /**
     * Input Event Catcher in main menu
     */
    Component inputEvent();

    /**
     * Dialog Input Event Catcher
     */
    Component dialogInputEvent();


    //title and headers
    /**
     * contains the title of the app and version number
     */
    Element title();
    
    /**
     * contains the Heading of the entries
     */
    Element tableHeader();
    
    /**
     * warns the user when the window is too small
     */
    Element warningWindow(Dimensions size);


    //dialog renderers
    /**
     * dynamically adds and removes components when using different dialogs
     * 
     * @param dialogLayer
    */
    void switchDialog(layers dialogLayer);

    /**
     * edit Dialog render 
    */    
    Element editPopup();
    
    /**
     * add Dialog render 
    */    
    Element addPopup();
    
    /**
     * remove Dialog render 
    */    
    Element remPopup();
    
    /**
     * remove Dialog render 
    */    
    Element newUser();
    
    /**
     * remove Master Password Dialog render 
    */
    Element masterPass();

    //main menu
    /**
     * Renders the Menu Entries in the main menu
     */
    Element menuRowEntry(const EntryState& state);
};
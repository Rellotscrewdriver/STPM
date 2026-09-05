#include "../tui.h"

void TUIFrontEnd::initComponents() {    
    applyStyle();
    initButtons();
    initOther();
    initInputs();
}

void TUIFrontEnd::applyStyle(){
    input.multiline = false;
    mInput.multiline = false;
    mInput.password = true;

    input.transform = [this](InputState state) {
        return inputStyle(state);
    };

    mInput.transform = [this](InputState state) {
        return inputMasterStyle(state);
    };
    
    saveOption.transform = [this](const EntryState& state) {
        return saveBtnStyle(state);
    };

    cancelOption.transform = [this](const EntryState& state) {
        return cancelBtnStyle(state);
    };

    genPassOption.transform = [this](const EntryState& state) {
        return genPassBtnStyle(state);
    };

    verifyOption.transform = [this](const EntryState& state) {
        return verifyBtnStyle(state);
    };
}

void TUIFrontEnd::initOther(){
    // Set up menu entry options & populate entries
    menuOption.entries_option.transform = [this](const EntryState& state) {
        return menuRowEntry(state);
    };
    db.updateMenuEnteries();

    menuComponent = ftxui::Menu(&(db.menuEntries), &selectedRow, menuOption);

    btnContainer = Container::Horizontal({ saveBtn, cancelBtn });

    dContainer = Container::Vertical({}, &dialogSelector);

    mainInputEvent = inputEvent();
    dInputEvent = dialogInputEvent();
}

void TUIFrontEnd::initButtons(){
    saveBtn = saveButton();
    yesBtn = confirmButton();
    noBtn = noButton();
    addBtn = addButton();
    checkBtn = checkButton();
    exitBtn = exitButton();
    cancelBtn = cancelButton();
    genPassBtn = genPassButton();
}

void TUIFrontEnd::initInputs(){
    auto rawEmailInput = Input(&emailCred, "Enter your Email...", input);
    auto rawSiteInput = Input(&siteCred, "Enter the Link...", input);
    
    // Catch keystrokes on input elements to re-evaluate validation on every keypress
    emailInput = CatchEvent(rawEmailInput, [this](Event event) {
        validateInputs(emailCred, siteCred);
        return false;
    });

    siteInput = CatchEvent(rawSiteInput, [this](Event event) {
        validateInputs(emailCred, siteCred);
        return false;
    });

    auto RawpassInput = Input(&masterPassT, "Enter Master Password...", mInput);
    passInput = CatchEvent(RawpassInput, [this](Event event) {
        passMsg = "";
        return false;
    });

    passInputDup = Input(&masterPassTDup, "Enter Master Password Again...", mInput);
}
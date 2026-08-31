#include "tui.h"

TUIFrontEnd::TUIFrontEnd(){
    db.data = {
        {"001", "Alice Smith", "Engineer"},
        {"002", "Bob Jones", "Designer"},
        {"003", "Charlie Brown", "Manager"}
    };
    activeLayer = layers::newUserD;
    initComponents();

    renderLayout();
}

void TUIFrontEnd::initComponents() {    
    // Set up menu entry options & populate entries
    menu_option.entries_option.transform = [this](const EntryState& state) {
        return menuRowEntry(state);
    };
    db.updateMenuEnteries();

    applyStyle();
    
    auto rawEmailInput = Input(&emailCred, "Enter your Email...", input);
    
    // Catch keystrokes on emailInput to re-evaluate validation on every keypress
    emailInput = CatchEvent(rawEmailInput, [this](Event event) {
        validateInputs(emailCred, siteCred);
        return false; // Return false so the Input component still processes text entry
    });

    // Instantiate persistent inputs
    auto rawSiteInput = Input(&siteCred, "Enter the Link...", input);

    siteInput = CatchEvent(rawSiteInput, [this](Event event) {
        validateInputs(emailCred, siteCred);
        return false; // Return false so the Input component still processes text entry
    });

    // passInput = Input(&masterPassword, "Enter Master Password...", input);
    
    auto rawPasswordInput = Input(&masterPassT, "Enter Master Password...", mInput);

    passInput = CatchEvent(rawPasswordInput, [this](Event event) {
        //validateInputs(emailCred, siteCred);
        return false; // Return false so the Input component still processes text entry
    });

    saveBtn = saveButton();
    yesBtn = confirmButton();
    noBtn = noButton();
    addBtn = addButton();
    checkBtn = checkButton();
    exitBtn = exitButton();
    cancelBtn = cancelButton();
    genPassBtn = genPassButton();


    // Instantiate persistent menu
    menuComponent = ftxui::Menu(&(db.menu_entries), &selected_row, menu_option);

    btnContainer = Container::Horizontal({ saveBtn, cancelBtn });

    dContainer = Container::Vertical({}, &dialogSelector);

    mainInputEvent = inputEvent();
    dInputEvent = dialogInputEvent();
}


void TUIFrontEnd::exec(){
    screen.Loop(renderer);
}


void TUIFrontEnd::renderLayout(){

    renderer = Renderer(layoutManager(), [&] {
        auto minSize = Terminal::Size();
        Element mainLayout = buildMainLayout();
        if (minSize.dimx <= minWidth || minSize.dimy <= minHeight) {
            return warningWindow(minSize);
        }

        if (activeLayer == masterPassD) {
            switchDialog(masterPassD);
            return masterPass();
        }

        if (activeLayer == newUserD) {
            switchDialog(newUserD);
            return newUser();
        }


        if (activeLayer == editDialog) {
            switchDialog(editDialog);
            return dbox({
                mainLayout | dim,
                editPopup()
            });
        }

        if (activeLayer == remDialog) {
            switchDialog(remDialog);
            return dbox({
                mainLayout | dim,
                remPopup()
            });
        }

        if (activeLayer == addDialog) {
            switchDialog(addDialog);
            return dbox({
                mainLayout | dim,
                addPopup()
            });
        }


        return mainLayout;
    });
}

Component TUIFrontEnd::layoutManager(){
    return Container::Tab({
        mainInputEvent,
        dInputEvent
    }, &layerNo);
}

Element TUIFrontEnd::buildMainLayout()
{
    return vbox({
        vbox({
            title(),
        }),
        separator(),
        vbox({
            tableHeader(),
            menuComponent->Render() | vscroll_indicator | yframe | flex
        }) | flex,
        separator(),
        vbox({
            paragraphAlignCenter("Shortcuts: [↑/↓] Navigate  [Enter] Edit  [n] Add  [d] Delete  [q] Quit"),
            paragraphAlignCenter("Status: " + db.status_message) | bold,
            paragraphAlignCenter(db.copyIns) | color(Color::GreenLight)
        })
    }) | borderRounded;
}

#include "tui.h"

TUIFrontEnd::TUIFrontEnd(){
    db.data = {
        {"001", "Alice Smith", "Engineer"},
        {"002", "Bob Jones", "Designer"},
        {"003", "Charlie Brown", "Manager"}
    };
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
        validateEmail(emailCred);
        return false; // Return false so the Input component still processes text entry
    });

    // Instantiate persistent inputs
    // emailInput = Input(&emailCred, "Enter your Email...", input);
    auto rawSiteInput = Input(&siteCred, "Enter the Link...", input);

    siteInput = CatchEvent(rawSiteInput, [this](Event event) {
        validateSite(siteCred);
        return false; // Return false so the Input component still processes text entry
    });

    // siteInput = Input(&siteCred, "Enter the Link...", input);
    masterPassword = Input(&siteCred, "Enter Master Password...", input);

    saveBtn = saveButton();
    yesBtn = confirmButton();
    noBtn = noButton();
    addBtn = addButton();

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

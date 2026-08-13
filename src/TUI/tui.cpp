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
    input.multiline = false;
    
    // Set up menu entry options & populate entries
    menu_option.entries_option.transform = [this](const EntryState& state) {
        return menuRowEntry(state);
    };
    updateMenuEnteries();

    // Instantiate persistent inputs
    emailInput  = Input(&emailCred, "Enter your Email...", input);
    siteInput   = Input(&siteCred, "Enter the Link...", input);
    masterPassword = Input(&siteCred, "Enter Master Password...", input);

    input.transform = [this](InputState state) {
        return inputStyle(state);
    };

    // Instantiate persistent menu
    menuComponent = ftxui::Menu(&(db.menu_entries), &selected_row, menu_option);

    //dContainer = dialogContainer();
    dContainer = Container::Vertical({
        emailInput,
        siteInput,
    }, &dialog_selector);

    mainInputEvent = inputEvent();
    dInputEvent = dialogInputEvent();
}

void TUIFrontEnd::exec(){
    screen.Loop(renderer);
}


void TUIFrontEnd::renderLayout(){
    renderer = Renderer(layoutManager(), [&] {
        auto minSize = Terminal::Size();

        if (minSize.dimx <= minWidth || minSize.dimy <= minHeight) {
            warningWindow(minSize);
        }

        buildMainLayout();

        if (activeLayer == editDialog) {
            auto dialog = editPopup();
        
            return dbox({
                buildMainLayout() | dim,
                dialog
            });
        }

        return buildMainLayout();
    });
}

Component TUIFrontEnd::layoutManager(){
    layerNo = activeLayer;
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

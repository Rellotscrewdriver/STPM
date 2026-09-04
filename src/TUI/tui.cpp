#include "tui.h"

TUIFrontEnd::TUIFrontEnd(){
    // db.data = {
    //     {"001", "Alice Smith", "Engineer"},
    //     {"002", "Bob Jones", "Designer"},
    //     {"003", "Charlie Brown", "Manager"}
    // };
    activeLayer = layers::newUserD;
    firstTimeSetup();
    initComponents();
    renderLayout();
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
            paragraphAlignCenter(db.mainNavText),
            paragraphAlignCenter("Status: " + db.statusMessage) | bold,
            paragraphAlignCenter(db.copyIns) | color(Color::GreenLight)
        })
    }) | borderRounded;
}

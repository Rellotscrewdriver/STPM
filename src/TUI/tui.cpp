#include "tui.h"

TUIFrontEnd::TUIFrontEnd(){
    data = {
        {"001", "Alice Smith", "Engineer"},
        {"002", "Bob Jones", "Designer"},
        {"003", "Charlie Brown", "Manager"}
    };
    renderLayout();    
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
    int layerNo = activeLayer;
    return Container::Tab({
        inputEvent(),
        dialogInputEvent()
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
            menu()->Render() | vscroll_indicator | yframe | flex
        }) | flex,
        separator(),
        vbox({
            paragraphAlignCenter("Shortcuts: [↑/↓] Navigate  [Enter] Edit  [n] Add  [d] Delete  [q] Quit"),
            paragraphAlignCenter("Status: " + status_message) | bold,
            paragraphAlignCenter(copyIns) | color(Color::GreenLight)
        })
    }) | borderRounded;
}

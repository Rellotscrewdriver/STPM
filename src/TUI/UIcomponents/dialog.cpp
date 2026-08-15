#include "../tui.h"

Component TUIFrontEnd::dialogContainer(){
    if(activeLayer == addDialog || activeLayer == editDialog){
        return Container::Vertical({
            emailInput,
            siteInput,
            btnLayout()
        }, &dialog_selector);
    } else if(activeLayer == editDialog || activeLayer == mainMenu){
        return Container::Vertical({
            emailInput,
            siteInput,
            genPassBtn,
            btnLayout()
        }, &dialog_selector);
    } else if(activeLayer == remDialog){
        return Container::Vertical({
            btnLayout()
        }, &dialog_selector);
    } else {
        return Container::Vertical({
            btnLayout()
        }, &dialog_selector);
    }
}

Element TUIFrontEnd::editPopup(){
    return window(text(" Edit Credential "), 
        vbox({
            paragraphAlignCenter(" Navigation: [↑/↓] Switch Fields  [←/→] Select Options ") | center,
            separator(),
            hbox(paragraph(" Email: "), emailInput->Render()),
            hbox(paragraph(" Site: "), siteInput->Render()),
            hbox(paragraph(" Regenerate Password: "), text(db.data[selected_row].id), genPassBtn->Render()),
            separator(),
            hbox(saveBtn->Render(), text("   "), cancelBtn->Render()) | center
        })
    ) | clear_under | center;
}

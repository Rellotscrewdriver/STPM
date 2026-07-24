#include "tui.h"

Component TUIFrontEnd::dialogContainer(){
    if(activeLayer == addDialog){
        return Container::Vertical({
            inputEmail(),
            inputSite(),
            btnLayout()
        }, &dialog_selector);
    } else if(activeLayer == editDialog){
        return Container::Vertical({
            inputEmail(),
            inputSite(),
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
            hbox(paragraph(" Email: "), inputEmail()->Render()),
            hbox(paragraph(" Site: "), inputSite()->Render()),
            hbox(paragraph(" Generate Password: "), genPassBtn()->Render()),
            separator(),
            hbox(saveBtn()->Render(), text("   "), cancelBtn()->Render()) | center
        })
    ) | clear_under | center;
}

#include "../tui.h"

void TUIFrontEnd::switchDialog(layers dialogLayer){
    layerNo = 1; // Route tab focus to dInputEvent

    dContainer->DetachAllChildren();

    if (dialogLayer == addDialog || dialogLayer == editDialog) {
        dContainer->Add(emailInput);
        dContainer->Add(siteInput);
        dContainer->Add(genPassBtn);
        dContainer->Add(btnContainer);
    } else if (dialogLayer == remDialog) {
        dContainer->Add(btnContainer);
    } else if (dialogLayer == masterPass) {
        dContainer->Add(masterPassword);
        dContainer->Add(btnContainer);
    }

    dContainer->TakeFocus();
}

Element TUIFrontEnd::editPopup(){
    maxDialogSelections = 3;
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

Element TUIFrontEnd::addPopup(){
    maxDialogSelections = 3;
    return window(text(" Add Credential "), 
        vbox({
            paragraphAlignCenter(" Navigation: [↑/↓] Switch Fields  [←/→] Select Options ") | center,
            separator(),
            hbox(paragraph(" Email: "), emailInput->Render()),
            hbox(paragraph(" Site: "), siteInput->Render()),
            //hbox(paragraph(" Regenerate Password: "), text(db.data[selected_row].id), genPassBtn->Render()),
            separator(),
            hbox(saveBtn->Render(), text("   "), cancelBtn->Render()) | center
        })
    ) | clear_under | center;
}

Element TUIFrontEnd::remPopup(){
    maxDialogSelections = 3;
    return window(text(" Remove Credential "), 
        vbox({
            paragraphAlignCenter(" Navigation: [←/→] Select Options ") | center,
            separator(),
            paragraphAlignCenter(" Are you sure you wanna remove this? ") | center,
            separator(),
            hbox(saveBtn->Render(), text("   "), cancelBtn->Render()) | center
        })
    ) | clear_under | center;
}

Element TUIFrontEnd::passPopup(){

}

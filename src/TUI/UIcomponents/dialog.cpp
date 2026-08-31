#include "../tui.h"

void TUIFrontEnd::switchDialog(layers dialogLayer){
    layerNo = 1; // Route tab focus to dInputEvent

    dContainer->DetachAllChildren();

    if (dialogLayer == addDialog || dialogLayer == editDialog) {
        dContainer->Add(emailInput);
        dContainer->Add(siteInput);
        dContainer->Add(genPassBtn);
        if(dialogLayer == editDialog){
            dContainer->Add(editBtnLayout());
        } else {
            dContainer->Add(addBtnLayout());
        }
    } else if (dialogLayer == remDialog) {
        dContainer->Add(remBtnLayout());
    } else if (dialogLayer == masterPassD || dialogLayer == newUserD) {
        dContainer->Add(passInput);
        dContainer->Add(passBtnLayout());
    }

    dContainer->TakeFocus();
}

Element TUIFrontEnd::editPopup(){
    maxDialogSelections = 3;

    validateInputs(emailCred, siteCred);
    
    return window(text(" Edit Credential "), 
        vbox({
            paragraphAlignCenter(" Navigation: [↑/↓] Switch Fields  [←/→] Select Options ") | center,
            separator(),
            hbox(paragraph(" Email:    "), emailInput->Render()),
            hbox(paragraph(" Site:     "), siteInput->Render()),
            hbox(
                paragraph("               "),
                isValidCredentials ? 
                paragraphAlignCenter("All good!") | color(Color::Green) 
                : paragraphAlignCenter(validationMsg) | color(Color::Red) | bold
            ),
            hbox(paragraph(" Password: "), genPassBtn->Render(), text(" " + db.data[selected_row].id)),
            separator(),
            hbox(saveBtn->Render(), text("   "), cancelBtn->Render()) | center
        })
    ) | clear_under | center;
}

Element TUIFrontEnd::addPopup(){
    maxDialogSelections = 3;

    validateInputs(emailCred, siteCred);

    return window(text(" Add Credential "), 
        vbox({
            paragraphAlignCenter(" Navigation: [↑/↓] Switch Fields  [←/→] Select Options ") | center,
            separator(),
            hbox(paragraph(" Email:    "), emailInput->Render()),
            hbox(paragraph(" Site:     "), siteInput->Render()),
            hbox(
                paragraph("               "),
                isValidCredentials ? 
                paragraphAlignCenter("All good!") | color(Color::Green) 
                : paragraphAlignCenter(validationMsg) | color(Color::Red) | bold
            ),
            hbox(paragraph(" Password: "), genPassBtn->Render(), text(" " + passCred)),
            separator(),
            hbox(addBtn->Render(), text("   "), cancelBtn->Render()) | center
        })
    ) | clear_under | center;
}

Element TUIFrontEnd::remPopup(){
    maxDialogSelections = 1;
    return window(text(" Remove Credential "), 
        vbox({
            paragraphAlignCenter(" Navigation: [←/→] Select Options ") | center,
            separator(),
            paragraphAlignCenter(" Are you sure you wanna remove this? ") | center,
            separator(),
            hbox(yesBtn->Render(), text("   "), noBtn->Render()) | center
        })
    ) | clear_under | center;
}

Element TUIFrontEnd::masterPass(){
    maxDialogSelections = 2;

    return window(
        text(""), 
        vbox({
            paragraphAlignCenter(" Navigation: [↑/↓] Switch Fields  [←/→] Select Options ") | center,
            separator(),
            paragraphAlignCenter(" Enter your Master Password "),
            passInput->Render(),
            hbox(
                paragraph("               "),
                isValidPassword ? 
                paragraphAlignCenter("Correct!") | color(Color::Green) 
                : paragraphAlignCenter(validationMsg) | color(Color::Red) | bold
            ),
            separator(),
            hbox(checkBtn->Render(), text("   "), exitBtn->Render()) | center
        })
    ) | clear_under | center;
}

Element TUIFrontEnd::newUser(){
    maxDialogSelections = 2;

    return window(text(""), 
        vbox({
            paragraphAlignCenter(" Navigation: [↑/↓] Switch Fields  [←/→] Select Options ") | center,
            separator(),
            paragraphAlignCenter("Make your new Master Password!"),
            passInput->Render(),
            hbox(
                paragraph("               "),
                isValidPassword ? 
                paragraphAlignCenter("Correct!") | color(Color::Green) 
                : paragraphAlignCenter(validationMsg) | color(Color::Red) | bold
            ),
            paragraphAlignCenter("Make sure to remember your password!\nelse it won't be recovered if you lost it!"),
            separator(),
            hbox(checkBtn->Render(), text("   "), exitBtn->Render()) | center
        })
    ) | clear_under | center;
}
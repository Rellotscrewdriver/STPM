#include "../tui.h"

void TUIFrontEnd::switchDialog(layers dialogLayer){
    layerNo = 1;

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
        if(dialogLayer == newUserD){
            dContainer->Add(passInputDup);
        }
        dContainer->Add(passBtnLayout());
    }

    dContainer->TakeFocus();
}

Element TUIFrontEnd::editPopup(){
    maxDialogSelect = 3;

    validateInputs(emailCred, siteCred);
    
    return window(text(" Edit Credential "), 
        vbox({
            paragraphAlignCenter(db.dialogNavText1) | center,
            separator(),
            hbox(paragraph(" Email:    "), emailInput->Render()),
            hbox(paragraph(" Site:     "), siteInput->Render()),
            hbox(
                paragraph("           "),
                isValidCredentials ? 
                paragraphAlignCenter("All good!") | color(Color::Green) 
                : paragraphAlignCenter(validationMsg) | color(Color::Red) | bold
            ),
            hbox(paragraph(" Password: "), genPassBtn->Render(), text(" " + siteDataNew[selectedRow].getPass())),
            separator(),
            hbox(saveBtn->Render(), text("   "), cancelBtn->Render()) | center
        })
    ) | clear_under | center;
}

Element TUIFrontEnd::addPopup(){
    maxDialogSelect = 3;

    validateInputs(emailCred, siteCred);

    return window(text(" Add Credential "), 
        vbox({
            paragraphAlignCenter(db.dialogNavText1) | center,
            separator(),
            hbox(paragraph(" Email:    "), emailInput->Render()),
            hbox(paragraph(" Site:     "), siteInput->Render()),
            hbox(
                paragraph("           "),
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
    maxDialogSelect = 1;
    return window(text(" Remove Credential "), 
        vbox({
            paragraphAlignCenter(db.dialogNavText2) | center,
            separator(),
            paragraphAlignCenter(" Are you sure you wanna remove this? ") | center,
            paragraphAlignCenter(siteDataNew[selectedRow].getLink()) | center | color(Color::Red),
            isDataEmpty ? paragraphAlignCenter("you can't delete a void entry!") | color(Color::Red) | bold 
            : paragraphAlignCenter(" "),
            separator(),
            hbox(yesBtn->Render(), text("   "), noBtn->Render()) | center
        })
    ) | clear_under | center;
}

Element TUIFrontEnd::masterPass(){
    maxDialogSelect = 2;

    return window(
        text(""), 
        vbox({
            paragraphAlignCenter(db.dialogNavText1) | center,
            separator(),
            paragraphAlignCenter(" Enter your Master Password "),
            passInput->Render(),
            hbox(
                isValidPassword ? 
                paragraphAlignCenter("Correct!") | color(Color::Green) 
                : paragraphAlignCenter(passMsg) | color(Color::Red) | bold
            ),
            separator(),
            hbox(checkBtn->Render(), text("   "), exitBtn->Render()) | center
        })
    ) | clear_under | center;
}

Element TUIFrontEnd::newUser(){
    maxDialogSelect = 3;

    return window(text(""), 
        vbox({
            paragraphAlignCenter(db.dialogNavText1) | center,
            separator(),
            paragraphAlignCenter("Make your new Master Password!"),
            passInput->Render(),
            passInputDup->Render(),
            hbox(
                isValidPassword ? 
                paragraphAlignCenter("Correct!") | color(Color::Green) 
                : paragraphAlignCenter(passMsg) | color(Color::Red) | bold
            ),
            paragraphAlignCenter("Make sure to remember your password!\nit won't be recovered if you lost it!"),
            separator(),
            hbox(checkBtn->Render(), text("   "), exitBtn->Render()) | center
        })
    ) | clear_under | center;
}

#include "../tui.h"

Element TUIFrontEnd::inputEleStyle(InputState state, Color focusBg, Color focusFg, Color idleBg, Color idleFg){
    if (state.focused) {
        return state.element | color(focusFg) | bgcolor(focusBg) | bold;
    }
    return state.element | color(idleFg) | bgcolor(idleBg) | underlined;
}

Element TUIFrontEnd::buttonEleStyle(const EntryState &state, Color focusBg, Color focusFg, Color activeBg, Color activeFg, Color idleBg, Color idleFg){
    auto element = text(" " + state.label + " ") | center;
    if (state.focused) {
        return element | bgcolor(focusBg) | color(focusFg) | bold;
    } else if (state.active) {
        return element | bgcolor(activeBg) | color(activeFg);
    }
    
    return element | bgcolor(idleBg) | color(idleFg);    
}


Element TUIFrontEnd::saveBtnStyle(const EntryState &state){
    return buttonEleStyle(state, 
        Color::GreenLight, Color::Black, 
        Color::Green, Color::Black, 
        Color::DarkGreen, Color::Black
    );
}

Element TUIFrontEnd::cancelBtnStyle(const EntryState &state){
    return buttonEleStyle(state, 
        Color::RedLight, Color::White,
        Color::DarkRedBis, Color::Black, 
        Color::Red, Color::White
    );    
}

Element TUIFrontEnd::genPassBtnStyle(const EntryState &state){
    return buttonEleStyle(state, 
        Color::DodgerBlue2, Color::White, 
        Color::Blue3, Color::White, 
        Color::NavyBlue, Color::White
    );
}


Element TUIFrontEnd::verifyBtnStyle(const EntryState &state){
    return buttonEleStyle(state, 
        Color::DodgerBlue1, Color::White, 
        Color::DeepSkyBlue4, Color::White, 
        Color::DeepSkyBlue3, Color::White
    );
}

Element TUIFrontEnd::inputStyle(InputState state){
    return inputEleStyle(state, 
        Color::Grey15, Color::CyanLight, 
        Color::Default, Color::White
    );
}

Element TUIFrontEnd::inputMasterStyle(InputState state){
    return inputEleStyle(state, 
        Color::Grey15, Color::CyanLight, 
        Color::Default, Color::White
    );
}
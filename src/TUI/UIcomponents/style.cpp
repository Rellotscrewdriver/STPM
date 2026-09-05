#include "../tui.h"

Element TUIFrontEnd::inputEleStyle(InputState state, Color focusBg, Color focusFg, Color idleBg, Color idleFg){
    if (state.focused) {
        return state.element | color(focusFg) | bgcolor(focusBg) | bold;
    } else {
        return state.element | color(idleFg) | bgcolor(idleBg) | underlined;
    }
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
    return buttonEleStyle(state, Color::Green, Color::Black, Color::GreenLight, Color::Black, Color::DarkGreen, Color::White);
}

Element TUIFrontEnd::cancelBtnStyle(const EntryState &state){
    return buttonEleStyle(state, Color::DarkRed, Color::White, Color::Red, Color::White, Color::DarkRedBis, Color::White);    
}

Element TUIFrontEnd::genPassBtnStyle(const EntryState &state){
    return buttonEleStyle(state, Color::DeepSkyBlue3Bis, Color::Black, Color::Blue, Color::Black, Color::NavyBlue, Color::White);
}

Element TUIFrontEnd::verifyBtnStyle(const EntryState &state){
    return buttonEleStyle(state, Color::DeepSkyBlue4Ter, Color::Black, Color::Blue1, Color::Black, Color::DarkGreen, Color::White);
}

Element TUIFrontEnd::inputStyle(InputState state){
    return inputEleStyle(state, Color::Grey27, Color::Blue, Color::Default, Color::Grey62);
}

Element TUIFrontEnd::inputMasterStyle(InputState state){
    return inputEleStyle(state, Color::Grey30, Color::Red, Color::Default, Color::Grey62);
}
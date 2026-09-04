#include "../tui.h"

Element TUIFrontEnd::saveBtnStyle(const EntryState &state){
    auto element = text(" " + state.label + " ") | center;
    if (state.focused) {
        return element | bgcolor(Color::Green) | color(Color::Black) | bold;
    } else if (state.active) {
        return element | bgcolor(Color::GreenLight) | color(Color::Black);
    }
    return element | bgcolor(Color::DarkGreen) | color(Color::White);
}

Element TUIFrontEnd::cancelBtnStyle(const EntryState &state){
    auto element = text(" " + state.label + " ") | center;
    if (state.focused) {
        return element | bgcolor(Color::Red) | color(Color::Black) | bold;
    } else if (state.active) {
        return element | bgcolor(Color::RedLight) | color(Color::Black);
    }
    // Default idle state
    return element | bgcolor(Color::DarkRed) | color(Color::White);
}

Element TUIFrontEnd::inputStyle(InputState state){
    if (state.focused) {
        return state.element | color(Color::Blue) | bgcolor(Color::Grey27) | bold | underlined;
    } else {
        // Default idle state
        return state.element | color(Color::Grey62) | bgcolor(Color::Default) | underlined;
    }
}

Element TUIFrontEnd::inputMasterStyle(InputState state){
    if (state.focused) {
        return state.element | color(Color::Red) | bgcolor(Color::Grey30) | bold | underlined;
    } else {
        // Default idle state
        return state.element | color(Color::Grey62) | bgcolor(Color::Default) | underlined;
    }
}
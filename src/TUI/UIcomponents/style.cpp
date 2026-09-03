#include "../tui.h"

void TUIFrontEnd::applyStyle(){
    input.multiline = false;
    mInput.multiline = false;

    input.transform = [this](InputState state) {
        return inputStyle(state);
    };

    mInput.transform = [this](InputState state) {
        return inputMasterStyle(state);
    };
    
    saveOption.transform = [this](const EntryState& state) {
        return saveBtnStyle(state);
    };

    cancelOption.transform = [this](const EntryState& state) {
        return cancelBtnStyle(state);
    };
}

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
    return element | bgcolor(Color::DarkRed) | color(Color::White);
}

Element TUIFrontEnd::inputStyle(InputState state){
    if (state.focused) {
        // Styled when selected via keyboard tab/arrows or mouse click
        return state.element | color(Color::Blue) | bgcolor(Color::Grey27) | bold | underlined;
    } else {
        // Default idle state
        return state.element | color(Color::Grey62) | bgcolor(Color::Default) | underlined;
    }
}

Element TUIFrontEnd::inputMasterStyle(InputState state){
    if (state.focused) {
        // Styled when selected via keyboard tab/arrows or mouse click
        return state.element | color(Color::Red) | bgcolor(Color::Grey30) | bold | underlined;
    } else {
        // Default idle state
        return state.element | color(Color::Grey62) | bgcolor(Color::Default) | underlined;
    }
}
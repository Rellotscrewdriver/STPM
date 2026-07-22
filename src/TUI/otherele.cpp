#include "tui.h"

Element TUIFrontEnd::title(){
    return hbox({
        paragraph("STPM - Simple Terminal Password Manager ") | bold,
        text("v1.0.0") | bold,
    }) | color(Color::Blue) | center;
}

Element TUIFrontEnd::tableHeader(){
    return hbox({
        text("ID")   | size(WIDTH, EQUAL, 20) | color(Color::Green) | bold | center,
        text("Name") | flex | color(Color::Green) | bold,
        text("Role") | size(WIDTH, EQUAL, 20) | color(Color::Green) | bold | center
    }) | bold;
}

Element TUIFrontEnd::warningWindow(Dimensions size){
    return vbox({
        paragraph("SCREEN DIMENSION TOO LOW!") | bold | color(Color::Red) | center,
        separator(),
        paragraph("Please expand or zoom out your terminal windows to view the UI properly.") | center,
        separatorEmpty(),
        text("Required: " + std::to_string(minWidth) + "x" + std::to_string(minHeight)) | color(Color::Red) | bold | center,
        text("Current:  " + std::to_string(size.dimx) + "x" + std::to_string(size.dimy)) | color(Color::Yellow) | center,
    }) | center | borderRounded;
}

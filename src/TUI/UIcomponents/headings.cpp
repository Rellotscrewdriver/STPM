#include "../tui.h"
#include "version.h"

Element TUIFrontEnd::title(){
    return hbox({
        paragraph("STPM - Simple TUI Password Manager ") | bold,
        text(Version::STRING) | bold,
    }) | color(Color::Blue) | center;
}

Element TUIFrontEnd::tableHeader(){
    return hbox({
        paragraphAlignLeft("Emails")   | size(WIDTH, EQUAL, 30) | color(Color::Green) | bold | center,
        paragraphAlignCenter("Site Names") | flex | color(Color::Green) | bold,
        paragraphAlignCenter("Passwords") | size(WIDTH, EQUAL, 30) | color(Color::Green) | bold | center
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

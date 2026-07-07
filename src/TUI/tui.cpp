#include "tui.h"

TUIFrontEnd::TUIFrontEnd(){
    // 1. Initialize ScreenInteractive for Fullscreen mode
    auto screen = ScreenInteractive::Fullscreen();

    // 2. Manage State variables
    int selected_menu_item = 0;
    std::vector<std::string> entries = {
        "Test1",
        "Test2",
        "Test3",
    };

    // 3. Create interactive components
    auto menu_options = MenuOption::Vertical();
    menu_options.on_enter = [&]() {
        if (selected_menu_item == 3) {
            screen.ExitLoopClosure(); // Terminate the fullscreen application loop cleanly
        }
    };

    auto sidebar_menu = Menu(&entries, &selected_menu_item, menu_options);

    // 4. Define the Layout and Geometry constraints
    auto renderer = Renderer(sidebar_menu, [&]() {
        // Stitch the UI panels together into a responsive, full-screen grid
        return hbox({
                text("STPM - Simple Terminal Password Manager") | bold,
                filler(), // Pushes text to the left, fills the middle gap
                text("v1.0.0 ")
            }) | bgcolor(Color::RGBA(0,0,0,0)) | color(Color::Blue);
    });

    // 5. Fire up the execution loop
    screen.Loop(renderer);
}
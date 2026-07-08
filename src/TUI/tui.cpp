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
        return combineMainLayout();
    });

    // 5. Fire up the execution loop
    screen.Loop(renderer);
}

Element TUIFrontEnd::combineMainLayout()
{
    return vbox({
        renderTitle(),
        hbox({
            filler(),
            //renderMainBox().Render(),
            filler()
        }) | bgcolor(Color::Grey0) | color(Color::Blue),
    });
}

Element TUIFrontEnd::renderTitle()
{
    return hbox({
        filler(),
        text("STPM - Simple Terminal Password Manager ") | bold,
        text("v1.0.0"),
        filler()
    }) | bgcolor(Color::Black) | color(Color::Blue);
}


Element TUIFrontEnd::renderShortcutsBox()
{
    return Element();
}

Element FormatTableRow(const std::string& col1, const std::string& col2, const std::string& col3, bool is_header = false) {
    auto base_style = is_header ? (bold | color(Color::Cyan)) : nothing;
    return hbox({
        text(" " + col1) | base_style | size(WIDTH, EQUAL, 20),
        separator(),
        text(" " + col2) | base_style | size(WIDTH, EQUAL, 25),
        separator(),
        text(" " + col3) | base_style | size(WIDTH, EQUAL, 25)
    });
}

Component TUIFrontEnd::renderMenuTable(const std::vector<siteObj>& vault_data, int* selected_row_out) {
    auto container = Container::Vertical({});

    if (vault_data.empty()) {
        return Renderer([]() { return text("No vault items found.") | dim | center; });
    }

    // Generate dynamic interactive menu lines matching each vector object
    std::vector<std::string> blank_entries; 
    for (size_t i = 0; i < vault_data.size(); ++i) {
        blank_entries.push_back(""); // Proxy placeholders for structural synchronization
    }

    auto menu_options = MenuOption::Vertical();
    
    // Custom renderer mapping line entry slots directly to styled tabular column block text rows
    menu_options.entries_option.transform = [vault_data](const EntryState& state) {
        const auto& item = vault_data[state.index];
        Element row_element = FormatTableRow(item.link, item.email, item.password, false);
        
        // Apply focus / selection block styling overrides dynamically
        if (state.focused) {
            row_element = row_element | bgcolor(Color::BlueLight) | color(Color::Black);
        } else if (state.active) {
            row_element = row_element | bgcolor(Color::Blue) | color(Color::White) | bold;
        }
        return row_element;
    };

    // Instantiate native vertical tracking component menu hook
    auto table_menu = Menu(&blank_entries, selected_row_out, menu_options);
    
    // Wrap inside a structural renderer to prefix the fixed layout Header Row
    return Renderer(table_menu, [table_menu]() {
        return vbox({
            FormatTableRow("Website / Link", "Email Address", "Password", true),
            separator(),
            table_menu->Render()
        }) | border;
    });
}
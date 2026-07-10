#include "tui.h"

struct Record {
    std::string id;
    std::string name;
    std::string role;
};

std::string PadString(const std::string& str, size_t width) {
    if (str.length() >= width) return str.substr(0, width - 1) + " ";
    return str + std::string(width - str.length(), ' ');
}

TUIFrontEnd::TUIFrontEnd(){
    auto screen = ScreenInteractive::Fullscreen();

    std::vector<Record> data = {
        {"001", "Alice Smith", "Engineer"},
        {"002", "Bob Jones", "Designer"},
        {"003", "Charlie Brown", "Manager"},
        {"004", "Diana Prince", "Security"},
        {"001", "Alice Smith", "Engineer"},
        {"002", "Bob Jones", "Designer"},
        {"003", "Charlie Brown", "Manager"},
        {"004", "Diana Prince", "Security"},
        {"001", "Alice Smith", "Engineer"},
        {"002", "Bob Jones", "Designer"},
        {"003", "Charlie Brown", "Manager"},
        {"004", "Diana Prince", "Security"},
    };

    int selected_row = 0;
    int active_layer = 0;
    bool show_dialog = false;

    std::string edit_name;
    std::string edit_role;

    MenuOption menu_option;
    menu_option.entries_option.transform = [&](const EntryState& state) {
        // Prevent out-of-bounds access
        if (state.index >= data.size()) return text(""); 
        
        const auto& row = data[state.index];

        // Build a dynamic row: ID (fixed 10) | Name (flexible) | Role (fixed 15)
        Element e = hbox({
            text(" " + row.id)   | size(WIDTH, EQUAL, 20),
            separator(), // Native FTXUI vertical line
            text(" " + row.name) | flex, 
            separator(),
            text(" " + row.role) | size(WIDTH, EQUAL, 20)
        }) | borderRounded;
        
        // Apply selection styles
        if (state.active) e = e | bold;
        if (state.focused) e = e | inverted;
        
        return e;
    };

    std::vector<std::string> menu_entries;
    auto update_menu_entries = [&]() {
        menu_entries.clear();
        for (size_t i = 0; i < data.size(); i++) {
            // Push empty strings; the text is handled by the transform function above
            menu_entries.push_back(""); 
        }
    };
    update_menu_entries();

    auto menu = Menu(&menu_entries, &selected_row, menu_option) | borderEmpty;

    auto input_name = Input(&edit_name, "Enter Username...");
    auto input_role = Input(&edit_role, "Enter Email...");

    auto btn_save = Button("Save", [&] {
        data[selected_row].name = edit_name;
        data[selected_row].role = edit_role;
        update_menu_entries();
        active_layer = 0;
    });

    auto btn_cancel = Button("Cancel", [&] {
        active_layer = 0;
    });

    auto button_row = ftxui::Container::Horizontal({
        btn_save, 
        btn_cancel
    });

    auto dialog_container = Container::Vertical({
        input_name,
        input_role,
        button_row
    });

    // ENHANCEMENT 1: Catch 'Escape' to close the dialog
    auto dialog_with_keys = CatchEvent(dialog_container, [&](Event event) {
        if (event == Event::Escape) {
            //show_dialog = false;
            active_layer = 0;
            return true; // Event handled
        }
        return false;
    });

    // ENHANCEMENT 2: Add Vim bindings (j/k) to the main menu
    auto main_container = CatchEvent(menu, [&](Event event) {
        if (show_dialog) return true; // Let the dialog handle events if it's open

        if (event == Event::Character('q')) {
            screen.Exit();
            return true;
        }
        if (event == Event::Character('j')) {
            //selected_row = std::min((int)data.size() - 1, selected_row + 1);
            return menu->OnEvent(Event::ArrowDown);
            return true;
        }
        if (event == Event::Character('k')) {
            //selected_row = std::max(0, selected_row - 1);
            return menu->OnEvent(Event::ArrowUp);
            //return true;
        }
        if (event == Event::Return) {
            edit_name = data[selected_row].name;
            edit_role = data[selected_row].role;
            active_layer = 1;
            dialog_container->TakeFocus();
            return true;
        }
        return false;
    });

    auto layout_manager = Container::Tab({
        main_container,
        dialog_with_keys
    }, &active_layer);

    auto renderer = Renderer(layout_manager, [&] {
        renderTitle();
        auto table_header = hbox({
            text(" ID")   | size(WIDTH, EQUAL, 10),
            separator(),
            text(" Name") | flex,
            separator(),
            text(" Role") | size(WIDTH, EQUAL, 15)
        }) | bold | color(Color::Blue) | borderRounded;

        auto table_ui = vbox({
            text(" Employee Database ") | bold | center,
            separator(),
            table_header, // Inject our dynamic header here
            separator(),
            menu->Render() | vscroll_indicator | yframe | flex,
            separator(),
            text(" Shortcuts: [↑/↓] or [j/k] Navigate   [Enter] Edit   [q] Quit ") | center | dim
        }) | borderRounded;

        if (active_layer == 1) {
            auto dialog_ui = window(text(" Edit Record "), 
                vbox({
                    text(" Navigation: [↑/↓] Switch Fields  [←/→] Select Options ") | center,
                    separator(),
                    hbox(text(" Name: "), input_name->Render()),
                    hbox(text(" Role: "), input_role->Render()),
                    separator(),
                    hbox(btn_save->Render(), text("   "), btn_cancel->Render()) | center
                })
            ) | clear_under | center;

            return dbox({
                table_ui | dim,
                dialog_ui
            });
        }

        return table_ui;
    });

    screen.Loop(renderer);
}


Element TUIFrontEnd::combineMainLayout()
{
    auto table = renderMenuTable(siteDataNew, 0);
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
        Element row_element;//FormatTableRow(item.link, item.email, item.password, false);
        
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
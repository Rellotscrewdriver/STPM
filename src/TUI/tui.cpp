#include "tui.h"

struct Record {
    std::string id;
    std::string name;
    std::string role;
};

TUIFrontEnd::TUIFrontEnd(){
    auto screen = ScreenInteractive::Fullscreen();

    std::vector<Record> data = {
        {"001", "Alice Smith", "Engineer"},
        {"002", "Bob Jones", "Designer"},
        {"003", "Charlie Brown", "Manager"},
        {"004", "Diana Prince", "Security"},
        {"005", "Alice Smith", "Engineer"},
        {"006", "Bob Jones", "Designer"},
        {"008", "Diana Prince", "Security"},
        {"009", "Alice Smith", "Engineer"},
        {"0010", "Bob Jones", "Designer"},
        {"0011", "Charlie Brown", "Manager"},
        {"0012", "Diana Prince", "Security"},
    };

    int selected_row = 0;
    int active_layer = 0;
    bool edit_layer = false;
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
            paragraph(row.id) | size(WIDTH, EQUAL, 20),
            paragraph(row.name) | flex, 
            paragraph(row.role) | size(WIDTH, EQUAL, 20),
        });
        

        if (state.focused){
            e = e | bgcolor(Color::Blue) | color(Color::Black) | bold;
        }
        
        return e;
    };

    menu_option.on_enter = [&]() {
    // Validate we are within bounds
        if (selected_row >= 0 && selected_row < data.size()) {
        // Grab the exact text you want to copy
        std::string text_to_copy = data[selected_row].name;
        }
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

    auto menu = Menu(&menu_entries, &selected_row, menu_option);

    ButtonOption save_option;
    save_option.transform = [](const EntryState& state) {
        auto element = text(" " + state.label + " ") | center;
        if (state.focused) {
            return element | bgcolor(Color::Green) | color(Color::Black) | bold;
        } else if (state.active) {
            return element | bgcolor(Color::GreenLight) | color(Color::Black);
        }
        return element | bgcolor(Color::DarkGreen) | color(Color::White);
    };

    ButtonOption cancel_option;
    cancel_option.transform = [](const EntryState& state) {
        auto element = text(" " + state.label + " ") | center;
        if (state.focused) {
            return element | bgcolor(Color::Red) | color(Color::Black) | bold;
        } else if (state.active) {
            return element | bgcolor(Color::RedLight) | color(Color::Black);
        }
        return element | bgcolor(Color::DarkRed) | color(Color::White);
    };

    InputOption input_opt_name;
    input_opt_name.transform = [](InputState state) {
        if (state.focused) {
            // Styled when selected via keyboard tab/arrows or mouse click
            return state.element | color(Color::Blue) | bgcolor(Color::GrayDark) | bold | underlined;
        } else {
            // Default idle state
            return state.element | color(Color::White);
        }
    };

    InputOption input_opt_role;
    input_opt_role.transform = [](InputState state) {
        if (state.focused) {
            return state.element | color(Color::Blue) | bgcolor(Color::GrayDark) | bold | underlined;
        } else {
            return state.element | color(Color::White);
        }
    };

    input_opt_name.multiline = false;
    input_opt_role.multiline = false;
    
    auto input_name = Input(&edit_name, "Enter Username...", input_opt_name);
    auto input_role = Input(&edit_role, "Enter Email...", input_opt_role);

    auto btn_save = Button("Save", [&] {
        data[selected_row].name = edit_name;
        data[selected_row].role = edit_role;
        update_menu_entries();
        active_layer = 0;
    }, save_option);

    auto btn_cancel = Button("Cancel", [&] {
        active_layer = 0;
    }, cancel_option);

    auto button_row = ftxui::Container::Horizontal({
        btn_save, 
        btn_cancel
    });
    
    int dialog_selector = 0;
    auto dialog_container = Container::Vertical({
        input_name,
        input_role,
        button_row
    }, &dialog_selector);

    // Add a new empty row
    auto add_row = [&]() {
        data.push_back({"007", "James Bond", "Secret Service Agent"});
        menu_entries.push_back(""); // Sync the menu
    };

    // Delete the currently selected row
    //TODO: add a confirmation dialog when removing
    auto delete_row = [&]() {
        if (data.size() <= 1) return; // Optional: Prevent deleting the last row

        data.erase(data.begin() + selected_row);
        menu_entries.erase(menu_entries.begin() + selected_row);

        // Ensure selection stays within bounds
        if (selected_row >= data.size()) {
            selected_row = data.size() - 1;
        }
    };

    // ENHANCEMENT 1: Catch 'Escape' to close the dialog
    auto dialog_with_keys = CatchEvent(dialog_container, [&](Event event) {
        if (event == Event::Escape) {
            active_layer = 0;
            return true; // Event handled
        }

        if (event == Event::ArrowDown) {
            if (dialog_selector < 2) {
                dialog_selector++;
                return true; // Consume the event
            }
            dialog_selector = 0; 
            return true;
        }
    
        if (event == Event::ArrowUp) {
            if (dialog_selector > 0) {
                dialog_selector--;
                return true; // Consume the event
            }
            dialog_selector = 2; 
            return true;
        }
        return false;
    });

    auto main_container = CatchEvent(menu, [&](Event event) {
        if (show_dialog) return true; // Let the dialog handle events if it's open

        if (event == Event::Character('q')) {
            screen.Exit();
            return true;
        }

        //Scrolling effect
        if (!data.empty()) {
            int max_index = static_cast<int>(data.size()) - 1;

            if ((event == Event::ArrowUp || event == Event::Character('k')) && selected_row == 0) {
                selected_row = max_index;
                return true;
            }

            // Loop Down: If at the last row and pressing Down or 'j', jump to the first row
            if ((event == Event::ArrowDown || event == Event::Character('j')) && selected_row == max_index) {
                selected_row = 0;
                return true;
            }
        }

        if (event == Event::Character('j')) {
            return menu->OnEvent(Event::ArrowDown);
        }

        if (event == Event::Character('k')) {
            return menu->OnEvent(Event::ArrowUp);
        }
        
        if (event == Event::Character('n')) {
            add_row();
            // active_layer = 1;
            // dialog_container->TakeFocus();
            return true;
        }

        if (event == Event::Character('d')) {
            delete_row();
            // active_layer = 1;
            // dialog_container->TakeFocus();
            return true;
        }

        //theme override
        if (event == Event::Character('a')) {
            active_layer = 1;
            dialog_container->TakeFocus();
            return true;
        }

        if (event == Event::Character('c')) {
            if (selected_row >= 0 && selected_row < data.size()) {
                std::string text_to_copy = data[selected_row].name; // Copying the "Name" column
                //copy_to_clipboard(text_to_copy);
            
                status_message = "✅ Copied Name: \"" + text_to_copy + "\" to clipboard!";
                return true; // Stop event propagation
            }
        }
    
        // Check if the user pressed 'r' or 'R' (for copying "Role")
        if (event == Event::Character('v')) {
            if (selected_row >= 0 && selected_row < data.size()) {
                std::string text_to_copy = data[selected_row].role; // Copying the "Role" column
                //copy_to_clipboard(text_to_copy);

                status_message = "✅ Copied Role: \"" + text_to_copy + "\" to clipboard!";
                return true; // Stop event propagation
            }
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

    bool is_loading = true;

    auto table_header = hbox({
        text("ID")   | size(WIDTH, EQUAL, 20) | color(Color::Green) | bold | center,
        text("Name") | flex | color(Color::Green) | bold,
        text("Role") | size(WIDTH, EQUAL, 20) | color(Color::Green) | bold | center
    }) | bold;
    
    auto renderer = Renderer(layout_manager, [&] {
        auto minSize = Terminal::Size();

        const int minHeight = 11;
        const int minWidth = 55;

        if (minSize.dimx <= minWidth || minSize.dimy <= minHeight) {
            return vbox({
                paragraph("SCREEN DIMENSION TOO LOW!") | bold | color(Color::Red) | center,
                separator(),
                paragraph("Please expand or zoom out your terminal windows to view the UI properly.") | center,
                separatorEmpty(),
                text("Required: " + std::to_string(minWidth) + "x" + std::to_string(minHeight)) | color(Color::Red) | bold | center,
                text("Current:  " + std::to_string(minSize.dimx) + "x" + std::to_string(minSize.dimy)) | color(Color::Yellow) | center,
            }) | center | borderRounded;
        }

        auto table_ui = vbox({
            vbox({
                renderTitle(),
            }),
            separator(),
            vbox({
                table_header,
                menu->Render() | vscroll_indicator | yframe | flex
            }) | flex,
            separator(),
            vbox({
                paragraphAlignCenter("Shortcuts: [↑/↓] Navigate  [Enter] Edit  [n] Add  [d] Delete  [q] Quit"),
                paragraphAlignCenter("Status: " + status_message) | bold,
                paragraphAlignCenter(copyIns) | color(Color::GreenLight),
            })
        }) | borderRounded;

        if (active_layer == 1) {
            auto dialog_ui = window(text(" Edit Record "), 
                vbox({
                    paragraphAlignCenter(" Navigation: [↑/↓] Switch Fields  [←/→] Select Options ") | center,
                    separator(),
                    hbox(paragraph(" Name: "), input_name->Render()),
                    hbox(paragraph(" Role: "), input_role->Render()),
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
        }) | color(Color::Blue),
    });
}

Element TUIFrontEnd::renderTitle()
{
    return hbox({
        paragraph("STPM - Simple Terminal Password Manager ") | bold,
        text("v1.0.0"),
    }) | color(Color::Blue) | center;
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
#include "tui.h"



TUIFrontEnd::TUIFrontEnd(){
    data = {
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

    input_opt_name.multiline = false;
    
    auto input_name = Input(&edit_name, "Enter Username...", input_opt_name);
    auto input_role = Input(&edit_role, "Enter Email...", input_opt_name);

    auto btn_save = Button("Save", [&] {
        data[selected_row].name = edit_name;
        data[selected_row].role = edit_role;
        updateMenuEnteries();
        active_layer = 0;
    }, save_option);

    auto btn_cancel = Button("Cancel", [&] {
        active_layer = 0;
    }, cancel_option);

    auto button_row = ftxui::Container::Horizontal({
        btn_save, 
        btn_cancel
    });
    

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
    inputEvent();
    dialogInputEvent();

    auto layout_manager = Container::Tab({
        main_container,
        dialog_with_keys
    }, &active_layer);

    bool is_loading = true;
    
    auto renderer = Renderer(layout_manager, [&] {
        auto minSize = Terminal::Size();

        if (minSize.dimx <= minWidth || minSize.dimy <= minHeight) {
            warningWindow(minSize);
        }

        buildMainLayout();

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
                buildMainLayout() | dim,
                dialog_ui
            });
        }

        return buildMainLayout();
    });

    screen.Loop(renderer);
}

void TUIFrontEnd::exec()
{
    //screen.Loop();
}

void TUIFrontEnd::renderLayout(){
    renderer = Renderer(layout_manager, [&] {
        auto minSize = Terminal::Size();

        if (minSize.dimx <= minWidth || minSize.dimy <= minHeight) {
            warningWindow(minSize);
        }

        buildMainLayout();

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
                buildMainLayout() | dim,
                dialog_ui
            });
        }

        return buildMainLayout();
    });
}

Element TUIFrontEnd::buildMainLayout(){
    return vbox({
        vbox({
            title(),
        }),
        separator(),
        vbox({
            tableHeader(),
            menu()->Render() | vscroll_indicator | yframe | flex
        }) | flex,
        separator(),
        vbox({
            paragraphAlignCenter("Shortcuts: [↑/↓] Navigate  [Enter] Edit  [n] Add  [d] Delete  [q] Quit"),
            paragraphAlignCenter("Status: " + status_message) | bold,
            paragraphAlignCenter(copyIns) | color(Color::GreenLight)
        })
    }) | borderRounded;
}



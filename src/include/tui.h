#pragma once

#include "includes.h"
#include <FTXUI/include/ftxui/ftxui.hpp>

using namespace ftxui;

struct Record {
    std::string id;
    std::string name;
    std::string role;
};

class TUIFrontEnd {
public:
    TUIFrontEnd();
    void exec();

private:
    std::string status_message = "nothing was copied to clipboard";
    std::string copyIns = "Use Arrows to navigate | Press 'c' to copy Name | Press 'v' to copy Role";
    int selected_row = 0;
    std::string copyCred;
    std::vector<Record> data;
    std::vector<std::string> menu_entries;
    layers active_layer;
    int selected_row = 0;
    int dialog_selector = 0;
    bool show_dialog = false;

    std::string edit_name;
    std::string edit_role;
    Element combineMainLayout();
    Element renderTitle();
    Element renderShortcutsBox();
    Component renderMenuTable(const std::vector<siteObj>& vault_data, int* selected_row_out);
    //Element renderDialog();
    Element menuRowEntry(const EntryState& state);
    Component menu();
    void updateMenuEnteries();
    MenuOption menu_option;
};
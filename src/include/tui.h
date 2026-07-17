#pragma once

#include "includes.h"
#include <FTXUI/include/ftxui/ftxui.hpp>

using namespace ftxui;

class TUIFrontEnd : Element {
public:
    TUIFrontEnd();

private:
    std::string status_message = "nothing was copied to clipboard";
    std::string copyIns = "Use Arrows to navigate | Press 'c' to copy Name | Press 'v' to copy Role";

    Element combineMainLayout();
    Element renderTitle();
    Element renderShortcutsBox();
    Component renderMenuTable(const std::vector<siteObj>& vault_data, int* selected_row_out);
    //Element renderDialog();
};
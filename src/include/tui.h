#pragma once

#include "includes.h"
#include <FTXUI/include/ftxui/ftxui.hpp>

using namespace ftxui;

class TUIFrontEnd : Element {
public:
    TUIFrontEnd();

private:

    Element combineMainLayout();
    Element renderTitle();
    Element renderShortcutsBox();
    Component renderMenuTable(const std::vector<siteObj>& vault_data, int* selected_row_out);
    //Element renderDialog();
};
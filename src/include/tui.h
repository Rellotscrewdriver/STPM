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
};
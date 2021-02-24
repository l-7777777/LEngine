#pragma once
#include <string>
#include <map>
#include <windows.h>
#include "FailedToOpenWindowException.h"
#include "../VoidP/Game.h"

class Window
{
public:
    // functions
    Window(std::wstring text, bool fullscreen);
    HWND GetHandle();

    // variables
    Game *game;
};

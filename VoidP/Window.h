#pragma once
#include <map>
#include <string>
#include <windows.h>
#include "FailedToOpenWindowException.h"
#include "Game.h"

class Window
{
public:
    // internal functions
    void Constructor(std::wstring text, bool fullscreen);
    
    // end-user functions
    Window(std::wstring text, bool fullscreen);
    HWND GetHandle();

    // internal variables
    static std::map<HWND, Window *> windows;
    bool fullscreen;
    HWND handle;
    std::wstring text;

    // end-user variables
    Game *game;
};

std::map<HWND, Window *> Window::windows = std::map<HWND, Window *>();
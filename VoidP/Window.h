#pragma once
#include <map>
#include <string>
#include <windows.h>
#include "FailedToOpenWindowException.h"

class Window
{
public:
    Window(std::wstring text, bool fullscreen);
    void Constructor(std::wstring text, bool fullscreen);
    HWND GetHandle();
    static std::map<HWND, Window *> windows;
    
    bool fullscreen;
    HWND handle;
    std::wstring text;
};

std::map<HWND, Window *> Window::windows = std::map<HWND, Window *>();
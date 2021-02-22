#pragma once
#include <map>
#include <string>
#include <windows.h>
#include "FailedToOpenWindowException.h"

class Window
{
public:
    Window(std::wstring text, bool fullscreen);
    HWND GetHandle();

private:
    static std::map<HWND, Window *> windows;
    HWND handle;
};

std::map<HWND, Window *> Window::windows = std::map<HWND, Window *>();
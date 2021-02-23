#pragma once
#include <string>
#include <map>
#include <windows.h>
#include "FailedToOpenWindowException.h"

class Window
{
public:
    Window(std::wstring text, bool fullscreen);
    HWND GetHandle();
};

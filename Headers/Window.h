#pragma once
#include <string>
#include <windows.h>
#include "FailedToOpenWindowException.h"

class Window
{
public:
    Window(std::wstring text, bool fullscreen);

private:
    HWND handle;
};

#include "Window.h"

#include <iostream>
#include <map>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

Window::Window(std::wstring text, bool fullscreen)
{
    std::cout << "E" << '\n';
    
    WNDCLASS wndClass;
    if (!GetClassInfo(nullptr, L"LEngineWindow", &wndClass))
    {
        wndClass = { };
        wndClass.lpszClassName = L"LEngineWindow";
        wndClass.lpfnWndProc = WindowProc;

        RegisterClass(&wndClass);
    }

    handle = CreateWindowEx(0,
        L"LEngineWindow",
        text.c_str(),
        fullscreen ? WS_POPUP : WS_OVERLAPPEDWINDOW | CS_OWNDC,

        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        nullptr,
        nullptr,
        nullptr,
        nullptr);

    if (handle == nullptr)
    {
        throw FailedToOpenWindowException();
    }

    windows.insert_or_assign(handle, this);

    ShowWindow(handle, fullscreen ? SW_MAXIMIZE : SW_NORMAL);
    
    while (true)
    {
        Sleep(100);
    }
}

HWND Window::GetHandle()
{
    return handle;
}

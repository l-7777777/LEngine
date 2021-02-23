#include "Window.h"

#include <iostream>
#include <map>
#include <string>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_PAINT:
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hWnd, &ps);

                Window *window = Window::windows[hWnd];

                RECT windowRect = ps.rcPaint;
                if (window->fullscreen)
                {
                    windowRect = {0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)};
                }

                FillRect(hdc, &windowRect, (HBRUSH)(COLOR_WINDOW+1));

                EndPaint(hWnd, &ps);
            }
            return 0;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void Window::Constructor(std::wstring text, bool fullscreen)
{
    this->fullscreen = fullscreen;
    
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
    
    SetCursor(LoadCursor(nullptr, IDC_ARROW));
    ShowWindow(handle, fullscreen ? SW_MAXIMIZE : SW_NORMAL);

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

DWORD WINAPI RunConstructor(LPVOID lParam)
{
    Window *window = (Window *)lParam;
    window->Constructor(window->text, window->fullscreen);
    return 0;
}

Window::Window(std::wstring text, bool fullscreen)
{
    this->text = text;
    this->fullscreen = fullscreen;
    
    CreateThread(nullptr, 0, RunConstructor, this, 0, nullptr);
}

HWND Window::GetHandle()
{
    return handle;
}

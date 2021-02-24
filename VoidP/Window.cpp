#include "Window.h"

#include <stdexcept>
#include <iostream>
#include <map>
#include <string>
#include <thread>

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
        case WM_KEYDOWN:
            {
                Window *window = Window::windows[hWnd];
                Game *game = window->game;
                if (game != nullptr)
                {
                    game->ReceiveInput(InputType::KeyDown, wParam, lParam & 0xFFFF, lParam & 0x0000FF);
                }
            }
        return 0;
        case WM_KEYUP:
            {
                Window *window = Window::windows[hWnd];
                Game *game = window->game;
                if (game != nullptr)
                {
                    game->ReceiveInput(InputType::KeyUp, wParam, lParam & 0xFFFF, lParam & 0x0000FF);
                }
            }
        return 0;
        case WM_CHAR:
            {
                Window *window = Window::windows[hWnd];
                Game *game = window->game;
                if (game != nullptr)
                {
                    game->ReceiveInput(InputType::KeyPress, wParam, lParam & 0xFFFF, lParam & 0x0000FF);
                    game->ReceiveInput(InputType::Character, wParam, lParam & 0xFFFF, lParam & 0x0000FF);
                }
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

Window::Window(std::wstring text, bool fullscreen)
{
    this->text = text;
    this->fullscreen = fullscreen;

    std::thread thread([&text, &fullscreen, this]() {
        Constructor(text, fullscreen);
    });

    thread.join();
}

HWND Window::GetHandle()
{
    return handle;
}
#include <iostream>

#include "../Headers/Window.h"

int main(int argc, char* argv[])
{
    Window window(L"Some Window", true);

    Game game(L"Test Game", GameType::TwoDimensions);
    window.game = &game;
    while (true)
    {
        Sleep(100);
    }
    return 0;
}

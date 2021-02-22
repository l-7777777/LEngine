#include <iostream>

#include "../Headers/Window.h"

int main(int argc, char* argv[])
{
    std::cout << "E" << '\n';
    Window window(L"Some Window", false);
    Window window2(L"Some other Window", true);
    std::cout << "E" << '\n';
    return 0;
}

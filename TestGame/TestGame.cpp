#include <iostream>

#include "../Headers/Window.h"

int main(int argc, char* argv[])
{
    std::cout << "E" << '\n';
    Window window(L"Some Window", true);
    std::cout << "E" << '\n';
    while (true) {}
    return 0;
}

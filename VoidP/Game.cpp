#include "Game.h"

#include <iostream>

#include <Windows.h>

Game::Game(std::wstring name, GameType type)
{
    this->name = name;
    this->type = type;
}

Game::Game() {}

void Game::ReceiveInput(InputType type, int code, int repeatCount, int scanCode)
{
    if (type == InputType::KeyPress || type == InputType::Character)
    {
        code = VkKeyScan(code);
    }
    std::cout << (int)type << ": " << (char)MapVirtualKey(code, MAPVK_VK_TO_CHAR) << '\n';
}

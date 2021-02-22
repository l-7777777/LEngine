#pragma once
#include <string>

#include "GameType.h"

class Game
{
public:
    Game(std::wstring name, GameType type);

private:
    std::wstring name;
    GameType type;
};

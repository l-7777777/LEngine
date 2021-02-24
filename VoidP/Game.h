#pragma once
#include <string>

#include "GameType.h"
#include "InputType.h"

class Game
{
public:
    // end-user functions
    Game(std::wstring name, GameType type);

    // internal functions
    Game();
    void ReceiveInput(InputType type, int code, int repeatCount, int scanCode);

    // internal variables
    std::wstring name;
    GameType type;
};

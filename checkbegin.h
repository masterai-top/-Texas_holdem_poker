#pragma once

#include<vector>

namespace game
{
    class GameRoot;

    namespace logic
    {
        namespace gamelogic
        {
            int CheckBegin(GameRoot *root);
            int RemoveUser(GameRoot *root, std::vector<long> vdelUser);
        }
    }
}


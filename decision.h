
#pragma once

#include<vector>

namespace game
{
    class GameRoot;

    namespace logic
    {
        namespace clientlogic
        {
            void Decision(long uid, const vector<char> &vecMsgData, GameRoot *root, bool timeOut = false);
        }
    }
}


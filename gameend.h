#pragma once

namespace game
{
    class GameRoot;

    namespace logic
    {
        namespace gamelogic
        {
            void GameEnd(GameRoot *root);
            int sendGameFinish2Room(GameRoot *root);
        }
    }
}


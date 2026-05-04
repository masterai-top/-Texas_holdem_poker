#pragma once

#include "common/macros.h"
#include "common/nndef.h"

using namespace nndef;
using namespace nninvalid;

namespace game
{
    class GameRoot;

    namespace process
    {
        class Process
        {
            DISALLOW_COPY_AND_ASSIGN(Process)

        private:
            /**
             *
            */
            Process();

            /**
             *
            */
            explicit Process(GameRoot *root, E_NN_STATE process);

        public:
            static Process *Create(GameRoot *root)
            {
                return new Process(root, nil_nnstate);
            }

            void gameInit(); //初始化

            void setProcess(E_NN_STATE process);
            void turnProcess(E_NN_STATE process);
            void nextProcess();

            E_NN_STATE getProcess() const
            {
                return _process;
            }

            inline GameRoot const *getRoot()
            {
                return _root;
            }

        protected:
            GameRoot *const _root;

            E_NN_STATE _process;
        };
    };
};

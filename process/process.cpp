#include "process/process.h"
#include "gameroot.h"
#include "utils/tarslog.h"
#include "logic/gamelogic/head.h"

namespace game
{
    namespace process
    {
        //
        Process::Process() : _root(NULL), _process(nil_nnstate)
        {
            LOG_FATAL("creator Process without root and process.");
        }

        //
        Process::Process(GameRoot *root, E_NN_STATE process): _root(root), _process(process)
        {

        }

        //
        void Process::gameInit()
        {
            _process = nil_nnstate;
        }

        //
        void Process::setProcess(E_NN_STATE process)
        {
            _process = process;
        }

        //
        void Process::turnProcess(E_NN_STATE process)
        {
            using namespace logic;

            long ts = TNowMS();
            _process = process;
            switch (process)
            {
            case NN_STATE_GAME_BEGIN:
                gamelogic::GameBegin(_root);
                break;
            case NN_STATE_FRONT_BET:
                gamelogic::FrontBet(_root);
                break;
            case NN_STATE_GAME_BANKER:
                gamelogic::GameBankerCommon(_root);
                break;
            case NN_STATE_HD_CARD:
                gamelogic::SendHdCard(_root);
                break;
            case NN_STATE_COMMON_CARD:
                gamelogic::SendComCard(_root);
                break;
            case NN_STATE_TURN_CARD:
                gamelogic::SendTurnCard(_root);
                break;
            case NN_STATE_RIVER_CARD:
                gamelogic::SendRiverCard(_root);
                break;
            case NN_STATE_GAME_END:
                gamelogic::GameEnd(_root);
                break;
            default:
                DLOG_TRACE("turn process error. state: " << process);
                break;
            }

            long value = 3;
            long diff = TNowMS() - ts;
            if (diff > value)
            {
                DLOG_TRACE("turn process, state: " << process << ", costTime: " << diff << ", roomid: " << _root->roomid());
            }
        }

        //
        void Process::nextProcess()
        {
            turnProcess(static_cast<E_NN_STATE>(_process + 1));
        }
    };
};

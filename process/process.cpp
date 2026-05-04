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
                if (gamelogic::CheckPaoma(_root))
                {
                    turnProcess(NN_STATE_PAOMA);
                }
                else
                {
                    gamelogic::SendComCard(_root);
                }
                break;
            case NN_STATE_TURN_CARD:
                if (gamelogic::CheckInsureHehe(_root))
                {
                    turnProcess(static_cast<E_NN_STATE>(_process + 3));
                }
                else
                {
                    if (gamelogic::CheckPaoma(_root))
                    {
                            turnProcess(NN_STATE_PAOMA);
                    }
                    else
                    {
                        gamelogic::SendTurnCard(_root);
                    }
                }
                break;
            case NN_STATE_RIVER_CARD:
                if (gamelogic::CheckInsureHehe(_root))
                {
                    turnProcess(static_cast<E_NN_STATE>(_process + 3));
                }
                else
                {
                    if (gamelogic::CheckPaoma(_root))
                    {
                        turnProcess(NN_STATE_PAOMA);
                    }
                    else
                    {
                        gamelogic::SendRiverCard(_root);
                    }
                }
                break;
            case NN_STATE_GAME_END:
                gamelogic::GameEnd(_root);
                break;
            case NN_STATE_INSURE_TURN:
            case NN_STATE_INSURE_RIVER:
                gamelogic::InsureNoticeHaha(_root);
                break;
            case NN_STATE_PAOMA:
                gamelogic::PaomaNotice(_root);
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
            // 如果现阶段是在保险阶段，那么下一个阶段，先反贼_process退回到相应阶段，进下一步
            if (_process == NN_STATE_INSURE_TURN || _process == NN_STATE_INSURE_RIVER)
            {
                _process = static_cast<E_NN_STATE>(_process - 4);
            }
            turnProcess(static_cast<E_NN_STATE>(_process + 1));
        }
    };
};

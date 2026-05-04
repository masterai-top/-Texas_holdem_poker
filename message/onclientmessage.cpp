#include "dz.pb.h"
#include "gameroot.h"
#include "utils/tarslog.h"
#include "common/macros.h"
#include "message/onclientmessage.h"
#include "logic/clientlogic/head.h"

namespace game
{
    namespace message
    {
        void onClientMessage(long uid, int eMSG, const vector<char> &vecMsgData, GameRoot *root)
        {
            using namespace logic;

            try
            {
                switch(static_cast<unsigned char>(eMSG))
                {
                //房间发起sitdown后，发该消息，类似于举手，只有命令字，无消息内容
                case XGameDZProto::NN_msg2cTestBegin_E:
                {
                    // DLOG_TRACE("Recived NN_msg2cTestBegin_E msg, uid: " << uid << ", msgSize = " << vecMsgData.size());
                    clientlogic::TestBegin(uid, vecMsgData, root);
                }
                break;

                //站起
                case XGameDZProto::NN_msg2cStand_E:
                {
                    // DLOG_TRACE("Recived NN_msg2cStand_E msg, uid: " << uid << ", msgSize = " << vecMsgData.size());
                    clientlogic::stand(uid, vecMsgData, root);
                }
                break;

                //坐下
                case XGameDZProto::NN_msg2cSit_E:
                {
                    // DLOG_TRACE("Recived NN_msg2cSit_E msg, uid: " << uid << ", msgSize = " << vecMsgData.size());
                    clientlogic::sit(uid, vecMsgData, root);
                }
                break;

                //下注请求及应答
                case XGameDZProto::NN_msg2csTokenBet_E:
                {
                    // DLOG_TRACE("Recived NN_msg2csTokenBet_E msg, uid: " << uid << ", msgSize = " << vecMsgData.size());
                    clientlogic::TokenBet(uid, vecMsgData, root);
                }
                break;

                case XGameDZProto::NN_msg2csGuessHdCard_E:
                {
                    // DLOG_TRACE("Recived NN_msg2csGuessHdCard_E msg, uid: " << uid << ", msgSize = " << vecMsgData.size());
                    clientlogic::GuessHdCard(uid, vecMsgData, root);
                }
                break;

                case XGameDZProto::NN_msg2csShowHdCard_E:
                case XGameDZProto::NN_msg2csSneakCard_E:
                {
                    // DLOG_TRACE("Recived NN_msg2csShowHdCard_E msg, uid: " << uid << ", msgSize = " << vecMsgData.size());
                    clientlogic::ShowHdCard(eMSG, uid, vecMsgData, root);
                }
                break;

                case XGameDZProto::NN_msg2csGameStation_E:
                {
                    // DLOG_TRACE("Recived NN_msg2csGameStation_E msg, uid: " << uid << ", msgSize = " << vecMsgData.size());
                    clientlogic::GameStation(uid, vecMsgData, root);
                }
                break;

                case XGameDZProto::NN_msg2csJoinQueue_E:
                case XGameDZProto::NN_msg2csQueueList_E:
                case XGameDZProto::NN_msg2csPause_E:
                {
                    // DLOG_TRACE("Recived NN_msg2csTestCard_E msg, uid: " << uid << ", msgSize = " << vecMsgData.size());
                    clientlogic::HandleQueue(eMSG, uid, vecMsgData, root);
                }
                break;

                //游戏记录
                case XGameDZProto::NN_msg2csGetRecord_E:
                {
                    clientlogic::GetRecord(uid, vecMsgData, root);
                }
                break;

                //收藏游戏记录
                case XGameDZProto::NN_msg2csCollectRecord_E:
                {
                    clientlogic::CollectRecord(uid, vecMsgData, root);
                }
                break;

                //取买入信息
                case XGameDZProto::NN_msg2csGetBuy_E:
                {
                    // DLOG_TRACE("Recived NN_msg2csGetBuy_E, uid: " << uid << ", msgSize = " << vecMsgData.size());
                    clientlogic::GetBuy(uid, vecMsgData, root);
                }
                break;

                //买入
                case XGameDZProto::NN_msg2cBuyChip_E:
                {
                    // DLOG_TRACE("Recived NN_msg2cBuyChip_E, uid: " << uid << ", msgSize = " << vecMsgData.size());
                    clientlogic::BuyChip(uid, vecMsgData, root);
                }
                break;

                //NN_msg2csShowComCard_E  = 131;  //查看公共牌
                case XGameDZProto::NN_msg2csMimiCard_E:
                case XGameDZProto::NN_msg2csShowComCard_E:
                {
                    // DLOG_TRACE("Recived NN_msg2csShowComCard_E, uid: " << uid << ", msgSize = " << vecMsgData.size());
                    clientlogic::ShowComCard(eMSG, uid, vecMsgData, root);
                }
                break;

                //NN_msg2csProlong_E      = 141;  //时间延长
                case XGameDZProto::NN_msg2csProlong_E:
                {
                    // DLOG_TRACE("Recived NN_msg2csProlong_E, uid: " << uid << ", msgSize = " << vecMsgData.size());
                    clientlogic::Prolong(uid, vecMsgData, root);
                }
                break;

                //NN_msg2csProlongInfo_E  = 142;  //时间延长信息
                case XGameDZProto::NN_msg2csProlongInfo_E:
                {
                    // DLOG_TRACE("Recived NN_msg2csProlongInfo_E, uid: " << uid << ", msgSize = " << vecMsgData.size());
                    clientlogic::ProlongInfo(uid, vecMsgData, root);
                }
                break;
                //
                case XGameDZProto::NN_msg2csTuoGuan_E:
                {
                    // DLOG_TRACE("Recived NN_msg2csTuoGuan_E, uid: " << uid << ", msgSize = " << vecMsgData.size());
                    clientlogic::TuoGuan(uid, vecMsgData, root);
                }
                break;
                // 保险
                case XGameDZProto::NN_msg2csInsure_E:
                {
                    DLOG_TRACE("Recived NN_msg2csInsure_E, uid: " << uid << ", msgSize = " << vecMsgData.size());
                    clientlogic::InsureActHehe(uid, vecMsgData, root);
                }
                break;
                // 申请跑马
                case XGameDZProto::NN_msg2sPaomaApply_E:
                {
                    DLOG_TRACE("Recived NN_msg2sPaomaApply_E, uid: " << uid << ", msgSize = " << vecMsgData.size());
                    clientlogic::PaomaApplyAct(uid, vecMsgData, root);
                }
                break;
                // 应答跑马
                case XGameDZProto::NN_msg2sPaomaAnswer_E:
                {
                    DLOG_TRACE("Recived NN_msg2sPaomaAnswer_E, uid: " << uid << ", msgSize = " << vecMsgData.size());
                    clientlogic::PaomaAnswerAct(uid, vecMsgData, root);
                }
                break;
                //
                default:
                {
                    LOG_ERROR("undefined network message from remote user, uid : " << uid << ", eMSG: " << eMSG);
                }
                break;
                }
            }
            catch (const TarsDecodeException &e)
            {
                ERROR(string("catch tars decode exception : ") + e.what());
            }
            catch (const TarsEncodeException &e)
            {
                ERROR(string("catch tars encode exception : ") + e.what());
            }
            catch (const TarsProtoException &e)
            {
                ERROR(string("catch proto exception : ") + e.what());
            }
            catch (const TC_Exception &e)
            {
                ERROR(string("catch tc exception : ") + e.what());
            }
            catch (const std::exception &e)
            {
                ERROR(string("catch std exception : ") + e.what());
            }
            catch (...)
            {
                ERROR("catch unknown exception.");
            }
        }
    };
};



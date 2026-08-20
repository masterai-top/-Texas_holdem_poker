#include "common/macros.h"
#include "common/nndef.h"
#include "gameroot.h"
#include "utils/tarslog.h"
#include "context/context.h"
#include "config/gameconfig.h"
#include "process/process.h"
#include "message/sendclientmessage.h"
#include "message/sendroommessage.h"

using namespace nndef;

namespace game
{
    namespace logic
    {
        namespace clientlogic
        {
            void TuoGuan(long uid, const vector<char> &vecMsgData, GameRoot *root)
            {
                __TRY__

                using namespace RoomSo;
                using namespace context;
                using namespace process;
                using namespace message;
                using namespace config;

                //解码
                XGameDDZProto::DDZ_msg2csTuoGuan shcm4 = pbToObj<XGameDDZProto::DDZ_msg2csTuoGuan>(vecMsgData);

                DLOG_TRACE("roomid:"<<root->roomid()<<", "<<"sit" << ", uid: " << uid << ", tuoguan:" << shcm4.btuoguan());

                XGameDDZProto::DDZ_msg2csTuoGuan shcm2;
                shcm2.set_iresultid(0);

                User *user = root->con->getUserByUid(uid);
                if(user != NULL)
                {
                    if(shcm4.btuoguan() ==  user->isTuoGuan())
                    {
                        shcm2.set_iresultid(-1);
                    }
                    else
                    {
                        user->setTuoGuan(shcm4.btuoguan());

                        if(!shcm4.btuoguan())
                        {
                            user->setTimeOut(0);
                        }
                        shcm2.set_btuoguan(user->isTuoGuan());
                        shcm2.set_icid(user->getCid());
                    }
                }
                else
                {
                    shcm2.set_iresultid(-2);
                }
                sendAllClientMessage<XGameDDZProto::DDZ_msg2csTuoGuan>(XGameDDZProto::DDZ_msg2csTuoGuan_E, shcm2, root);
                __CATCH__
            }
        }
    }
}

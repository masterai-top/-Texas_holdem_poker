#ifndef _OrderServantImp_H_
#define _OrderServantImp_H_

#include "servant/Application.h"
#include "OrderServant.h"
#include "Order.pb.h"
#include "XGameComm.pb.h"
#include "CommonStruct.pb.h"
#include "Push.h"

/**
 *订单服务接口
 *
 */
class OrderServantImp : public order::OrderServant
{
public:
    /**
     *
     */
    virtual ~OrderServantImp() {}

    /**
     *
     */
    virtual void initialize();

    /**
     *
     */
    virtual void destroy();

public:
    //消费，补单
    virtual tars::Int32 consumptionVerify(const order::ConsumptionVerifyReq &req, order::ConsumptionVerifyResp &rsp, tars::TarsCurrentPtr current);
    //校验订单
    virtual tars::Int32 orderVerify(const order::OrderVerifyReq &req, order::OrderVerifyResp &rsp, tars::TarsCurrentPtr current);
    //产生订单
    virtual tars::Int32 orderYield(const order::OrderYieldReq &req, order::OrderYieldResp &rsp, tars::TarsCurrentPtr current);
    //tcp请求处理接口
    virtual tars::Int32 onRequest(tars::Int64 lUin, const std::string &sMsgPack, const std::string &sCurServrantAddr, const JFGame::TClientParam &stClientParam,  const JFGame::UserBaseInfoExt &stUserBaseInfo, tars::TarsCurrentPtr current);

private:
    //校验订单
    int onOrderVerify(const XGameComm::TPackage &pkg, const std::string &sCurServrantAddr, const orderProto::OrderVerifyReq &req, tars::TarsCurrentPtr current);
    //产生订单
    int onOrderYield(const XGameComm::TPackage &pkg, const std::string &sCurServrantAddr, const orderProto::OrderYieldReq &req, tars::TarsCurrentPtr current);
    //消费，补单
    int onConsumptionVerify(const XGameComm::TPackage &pkg, const std::string &sCurServrantAddr, const orderProto::ConsumptionVerifyReq &req, tars::TarsCurrentPtr current);

private:
    //发送消息到客户端
    template<typename T>
    int toClientPb(const XGameComm::TPackage &tPackage, const std::string &sCurServrantAddr, XGameProto::ActionName actionName, XGameComm::MSGTYPE type, const T &t);

private:
    std::map<int64_t, JFGame::UserBaseInfoExt> _userInfo; //用户基本信息
    std::map<int64_t, string> _userIp;  //用户IP
};

/////////////////////////////////////////////////////
#endif

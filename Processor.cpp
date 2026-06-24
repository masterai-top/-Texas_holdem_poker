#include "Processor.h"
#include "globe.h"
#include "LogComm.h"
#include "DataProxyProto.h"
#include "ServiceDefine.h"
#include "util/tc_hash_fun.h"
#include "uuid.h"
#include "OrderServer.h"

//
using namespace std;
using namespace dataproxy;
using namespace dbagent;

/**
 * 
*/
Processor::Processor()
{
}

/**
 * 
*/
Processor::~Processor()
{
}

//ORDER_IOS      = 87,  //tb_ios_order
//查询
int Processor::selectIOSOrder()
{
    // int iRet = 0;

    // dataproxy::TReadDataReq dataReq;
    // dataReq.keyName = I2S(E_REDIS_TYPE_HASH) + ":" + I2S(USER_STATE_ONLINE) + ":" + L2S(uid);
    // dataReq.operateType = E_REDIS_READ;

    // dataReq.clusterInfo.busiType = E_PROPERTY;
    // dataReq.clusterInfo.frageFactorType = E_FRAGE_FACTOR_USER_ID;
    // dataReq.clusterInfo.frageFactor = uid;

    // vector<TField> fields;
    // TField tfield;
    // tfield.colArithType = E_NONE;
    // tfield.colName = "access";
    // tfield.colType = STRING;
    // fields.push_back(tfield);

    // dataReq.fields = fields;

    // TReadDataRsp dataRsp;
    // iRet = g_app.getOuterFactoryPtr()->getDataProxyServantPrx()->read(dataReq, dataRsp);
    // ROLLLOG_DEBUG << "online state, iRet: " << iRet << ", dataRsp: " << printTars(dataRsp) << endl;
    // //请求异常或应答错误
    // if(iRet != 0 || dataRsp.iResult != 0)
    // {
    //     ROLLLOG_ERROR << "online state err, iRet: " << iRet << ", iResult: " << dataRsp.iResult << endl;
    //     return -1;
    // }

    // ///取access addr
    // string addr;
    // for(auto it = dataRsp.fields.begin(); it != dataRsp.fields.end(); ++it)
    // {
    //     for(auto itaddr = it->begin(); itaddr != it->end(); ++itaddr)
    //     {
    //         if(itaddr->colName == "access")
    //         {
    //             addr = itaddr->colValue;
    //             break;
    //         }
    //     }
    // }

    // //返回数据
    // onlineState.state = userstate::E_ONLINE_STATE_ONLINE;
    // onlineState.accessAddr = addr;

    return 0;
}

//增加
int Processor::UpdateIOSOrder()
{
    // int iRet = 0;

    // dataproxy::TWriteDataReq wdataReq;
    // wdataReq.keyName = I2S(E_REDIS_TYPE_HASH) + ":" + I2S(USER_STATE_ONLINE) + ":" + L2S(uid);
    // wdataReq.operateType = E_REDIS_WRITE;

    // wdataReq.clusterInfo.busiType = E_PROPERTY;
    // wdataReq.clusterInfo.frageFactorType = E_FRAGE_FACTOR_USER_ID;
    // wdataReq.clusterInfo.frageFactor = uid;

    // vector<TField> fields;
    // TField tfield;
    // tfield.colArithType = E_NONE;
    // fields.clear();
    
    // tfield.colName = "access";
    // tfield.colType = STRING;
    // tfield.colValue = accessAddr;
    // fields.push_back(tfield);

    // //
    // wdataReq.fields = fields;

    // //
    // TWriteDataRsp wdataRsp;
    // iRet = g_app.getOuterFactoryPtr()->getDataProxyServantPrx()->write(wdataReq, wdataRsp);
    // ROLLLOG_DEBUG << "set user access addr data, iRet: " << iRet << ", wdataRsp: " << printTars(wdataRsp) << endl;
    // //请求异常或应答错误
    // if(iRet != 0 || wdataRsp.iResult != 0)
    // {
    //     ROLLLOG_ERROR << "save user access addr data err, iRet: " << iRet << ", iResult: " << wdataRsp.iResult << endl;
    //     return -1;
    // }

    return 0;
}












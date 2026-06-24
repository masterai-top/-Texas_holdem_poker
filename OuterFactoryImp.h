#ifndef _OUTER_FACTORY_IMP_H_
#define _OUTER_FACTORY_IMP_H_

#include <string>
#include <map>
#include "servant/Application.h"
#include "globe.h"
#include "OuterFactory.h"
#include "LogComm.h"

//wbl
#include <wbl/regex_util.h>

//配置服务
#include "DBAgentServant.h"
#include "OrderServant.h"
#include "HallServant.h"
#include "ActivityServant.h"
#include "ConfigServant.h"
#include "Log2DBServant.h"

//
using namespace dataproxy;
using namespace dbagent;

//时区
#define ONE_DAY_TIME (24*60*60)
#define ZONE_TIME_OFFSET (8*60*60)

//
class OuterFactoryImp;
typedef TC_AutoPtr<OuterFactoryImp> OuterFactoryImpPtr;

/**
 * 外部工具接口对象工厂
 */
class OuterFactoryImp : public OuterFactory
{
private:
    /**
     *
    */
    OuterFactoryImp();

    /**
     *
    */
    ~OuterFactoryImp();

    /**
     *
     */
    friend class OrderServantImp;

    /**
     *
     */
    friend class OrderServer;

public:
    //框架中用到的outer接口(不能修改):
    const OuterProxyFactoryPtr &getProxyFactory() const
    {
        return _pProxyFactory;
    }

    tars::TC_Config &getConfig() const
    {
        return *_pFileConf;
    }

public:
    //读取所有配置
    void load();
    //代理配置
    void readPrxConfig();
    //打印代理配置
    void printPrxConfig();

private:
    //
    void createAllObject();
    //
    void deleteAllObject();

public:
    //游戏配置服务代理
    const config::ConfigServantPrx getConfigServantPrx();
    //金猪服务代理
    const activity::ActivityServantPrx getActivityServantPrx(const long uid);
    //数据库代理服务代理
    const DBAgentServantPrx getDBAgentServantPrx(const long uid);
    //数据库代理服务代理
    const DBAgentServantPrx getDBAgentServantPrx(const string key);
    //广场服务代理
    const hall::HallServantPrx getHallServantPrx(const long uid);
    //广场服务代理
    const hall::HallServantPrx getHallServantPrx(const string key);
    //日志入库服务代理
    const DaqiGame::Log2DBServantPrx getLog2DBServantPrx(const long uid);
    //验证URL
    const string &getVerifyUrl(order::Eum_Channel_Type channelType, order::Eun_Order_Env env)
    {
        try
        {
            return this->_urls.at(channelType).at(env);
        }
        catch (const std::exception &)
        {
            ostringstream os;
            os << __FILE__ << ":" << __LINE__ << ":getVerifyUrl() failed! channelType : " << channelType << ",env : " << env << endl;
            throw logic_error(os.str());
        }
    }
    //获取产品价格
    string getProductPrice(int qrCode)
    {
        string value = I2S(qrCode);
        for (const auto &item : mallConfigRaw)
        {
            if (item.at("qrCode") == value)
            {
                string price = item.at("payValue");
                string originalPrice = price;

                //
                price = getProductPayValue(originalPrice);

                ///
                ROLLLOG_DEBUG << "originalPrice: " << originalPrice << ", price: " << price << endl;
                return price;
            }
        }

        for (const auto &item : activityConfigRaw)
        {
            if (item.at("level") == value)
            {
                string price = item.at("purchaseAmount");
                string originalPrice = price;

                //
                price = getProductPayValue(originalPrice);

                ///
                ROLLLOG_DEBUG << "originalPrice: " << originalPrice << ", price: " << price << endl;
                return price;
            }
        }
        throw logic_error("cant not find good, qrcode : " + value);
    }

    //解析商品价格
    string getProductPayValue(const string &price)
    {
        string retValue = "0";

        vector<string> vecprice = split(price, ".");

        // //
        // ostringstream os;
        // for(auto it : vecprice)
        // {
        //  os << it << " ";
        // }
        // ROLLLOG_DEBUG << os.str() << endl;

        if(vecprice.size() == 1)
        {
            retValue = I2S(S2I(vecprice[0]) * 100);
        }
        else if(vecprice.size() == 2)
        {
            string subStr = vecprice[1].substr(0, 2);
            retValue = I2S(S2I(vecprice[0]) * 100 + S2I(subStr));
        }

        //
        return retValue;
    }

    void asyncLog2DB(const int64_t uid, const DaqiGame::TLog2DBReq &req);

public:
    //格式化时间
    string GetTimeFormat();
    //获得时间秒数
    int GetTimeTick(const string &str);
private:
    //拆分字符串成整形
    int splitInt(string szSrc, vector<int> &vecInt);
    //拆分字符串
    vector<std::string> split(const string &str, const string &pattern);

private:
    //读写锁，防止脏读
    wbl::ReadWriteLocker m_rwlock;

private:
    //框架用到的共享对象(不能修改):
    tars::TC_Config *_pFileConf;
    //
    OuterProxyFactoryPtr _pProxyFactory;

private:
    //数据库代理服务
    std::string _DBAgentServantObj;
    DBAgentServantPrx _DBAgentServerPrx;

    std::string _HallServantObj;
    hall::HallServantPrx _HallServerPrx;

    std::string _ActivityServantObj;
    activity::ActivityServantPrx _ActivityServerPrx;

    //
    std::string _ConfigServantObj;
    config::ConfigServantPrx _ConfigServantPrx;

    //日志入库服务
    std::string _Log2DBServantObj;
    DaqiGame::Log2DBServantPrx _Log2DBServerPrx;

private:
    //
    vector<map<string, string>> mallConfigRaw;
    //
    vector<map<string, string>> activityConfigRaw;

private:
    // ios ---> debug(release)--->url
    std::map<order::Eum_Channel_Type, std::map<order::Eun_Order_Env, std::string>> _urls;
};

////////////////////////////////////////////////////////////////////////////////
#endif



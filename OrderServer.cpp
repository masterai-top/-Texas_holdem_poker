#include "OrderServer.h"
#include "OrderServantImp.h"
#include "curl/curl.h"
#include "LogComm.h"

//
using namespace std;

//
OrderServer g_app;

/////////////////////////////////////////////////////////////////
void
OrderServer::initialize()
{
    //initialize application here:
    //...

    addServant<OrderServantImp>(ServerConfig::Application + "." + ServerConfig::ServerName + ".OrderServantObj");

    //初始化外部接口对象
    initOuterFactory();

    // 注册动态加载命令
    TARS_ADD_ADMIN_CMD_NORMAL("reload", OrderServer::reloadSvrConfig);

    // 只需要初始化一次
    CURLcode returnCode = curl_global_init(CURL_GLOBAL_ALL);
    if (returnCode != CURLE_OK)
    {
        ROLLLOG_ERROR << "init curl failed!" << endl;
        sleep(5);
        terminate();
    }
}

/*
* 配置变更，重新加载配置
*/
bool OrderServer::reloadSvrConfig(const string &command, const string &params, string &result)
{
    try
    {
        getOuterFactoryPtr()->load();
        result = "reload server config success.";
        LOG_DEBUG << "reloadSvrConfig: " << result << endl;
        return true;
    }
    catch (TC_Exception const &e)
    {
        result = string("catch tc exception: ") + e.what();
    }
    catch (std::exception const &e)
    {
        result = string("catch std exception: ") + e.what();
    }
    catch (...)
    {
        result = "catch unknown exception.";
    }

    result += "\n fail, please check it.";
    LOG_DEBUG << "reloadSvrConfig: " << result << endl;
    return true;
}

/////////////////////////////////////////////////////////////////
void OrderServer::destroyApp()
{
    //destroy application here:
    //...
}

int OrderServer::initOuterFactory()
{
    _pOuter = new OuterFactoryImp();
    return 0;
}

/////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
    try
    {
        g_app.main(argc, argv);
        g_app.waitForShutdown();
    }
    catch (std::exception &e)
    {
        cerr << "std::exception:" << e.what() << std::endl;
    }
    catch (...)
    {
        cerr << "unknown exception." << std::endl;
    }
    return -1;
}
/////////////////////////////////////////////////////////////////

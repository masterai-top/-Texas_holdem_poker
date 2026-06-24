#ifndef _OrderServer_H_
#define _OrderServer_H_

#include <iostream>
#include "servant/Application.h"
#include "OuterFactoryImp.h"

//
using namespace tars;

/**
 *
 **/
class OrderServer : public Application
{
public:
    /**
     *
     **/
    virtual ~OrderServer() {};

    /**
     *
     **/
    virtual void initialize();

    /**
     *
     **/
    virtual void destroyApp();

public:
    /*
    * 配置变更，重新加载配置
    */
    bool reloadSvrConfig(const string &command, const string &params, string &result);

public:
    // 初始化外部对象接口
    int initOuterFactory();

    // 取外部对象接口
    OuterFactoryImpPtr getOuterFactoryPtr()
    {
        return _pOuter;
    }

private:
    OuterFactoryImpPtr _pOuter;
};

//
extern OrderServer g_app;

////////////////////////////////////////////
#endif

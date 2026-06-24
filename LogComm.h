#ifndef __LOGCOMM_H__
#define __LOGCOMM_H__

//
#include <util/tc_logger.h>
#include "servant/RemoteLogger.h"

//
using namespace tars;

//
#define ROLLLOG(level) (LOG->level() << "[" << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << "] ")
#define ROLLLOG_DEBUG (ROLLLOG(debug))
#define ROLLLOG_INFO (ROLLLOG(info))
#define ROLLLOG_WARN (ROLLLOG(warn))
#define ROLLLOG_ERROR (ROLLLOG(error))

#define FUNC_ENTRY(in) (ROLLLOG(debug) << ">>>> Enter " << __FUNCTION__ << "() in(" << in << ")" << endl)
#define FUNC_EXIT(out, ret) (ROLLLOG(debug) << "<<<< Exit " << __FUNCTION__ << "() out[" << out << "], ret = " << ret << endl)

#define FDLOG_ERROR (FDLOG("error") << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << "|")
#define FDLOG_EXCEPT (FDLOG("except") << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << "|")

//配置信息
#define FDLOG_CONFIG_INFO (FDLOG("config_info") << "|")

//充值日志
#define	FDLOG_RECHARGE_LOG (FDLOG("recharge_log") << "|")

//
#define FDLOG_INIT_FORMAT(x,y,z) (TarsTimeLogger::getInstance()->initFormatWithType<LogByMinute>(x,y,z))
#define FDLOG_RECHARGE_LOG_FORMAT (FDLOG_INIT_FORMAT("recharge_log", "%Y%m%d%H%M", 5))

template<typename T>
std::string toString(T t) {
	ostringstream os;
	os << t;
	return os.str();
}
template<typename T, typename... Args>
std::string toString(T head, Args... args) {
	ostringstream os;
	os << head;
	return os.str() + toString(args...);
}

#define THROW_LOGIC_ERROR(...) throw logic_error(toString("[", __FILE__, ":" , __LINE__ , ":" , __FUNCTION__ , "] ", __VA_ARGS__))

//接口性能边界值
#define COST_MS 100

#endif


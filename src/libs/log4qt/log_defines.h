#ifndef LOG_DEFINES_H
#define LOG_DEFINES_H
#include "log4qt/logger.h"

#define LOG_DEBUG(str) Log4Qt::Logger::logger("mainLogger")->debug(str)
#define LOG_WARN(str) Log4Qt::Logger::logger("mainLogger")->warn(str)
#define LOG_INFO(str) Log4Qt::Logger::logger("mainLogger")->info(str)
#define LOG_ERROR(str) Log4Qt::Logger::logger("mainLogger")->error(str)
#endif // LOG_DEFINES_H

#ifndef __LOG_H__
#define __LOG_H__

#include <fmt/format.h>
#include <glog/logging.h>

#define FORMAT_STRING fmt::format
#define LOG_FUNCTION LOG(INFO) << __FUNCTION__ << " | "
#define LOG_OUTPUT LOG_FUNCTION << FORMAT_STRING

#endif // LOG_H

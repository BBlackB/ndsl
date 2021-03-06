////
// @file TimeStampTest.cc
// @brief
// 测试TimeStamp
//
// @author zhangsiqi
// @email 1575033031@qq.com
//
#include "../catch.hpp"
#include <string.h>
#include <ndsl/utils/Log.h>

TEST_CASE("utils/Log")
{
    SECTION("LOG")
    {
        set_ndsl_log_sinks(LOG_SOURCE_EPOLL | LOG_SOURCE_EVENTLOOP,LOG_OUTPUT_FILE);
        LOG(LOG_ERROR_LEVEL, LOG_SOURCE_EVENTLOOP, "hello, world\n");
        LOG(LOG_ERROR_LEVEL, LOG_SOURCE_EPOLL, "debug\n");
    }

}
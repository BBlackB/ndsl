////
// @file Log.cc
// @brief
// 实现日志
//
// @author zhangsiqi
// @email 1575033031@qq.com
//
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <syslog.h>
#include <stdarg.h>
#include <ndsl/utils/Log.h>
#include <ndsl/utils/TimeStamp.h>

int tag = 0;

////
// @biref
// 文件
//

class Filelog
{
  private:
    int m_file;

  public:
    Filelog()
        : m_file(-1)
    {
        // init();
    }
    ~Filelog()
    {
        if (m_file != -1) ::close(m_file);
    }
    void init()
    {
        char path[256];
        ndsl::utils::TimeStamp ts;
        ts.now();
        ts.to_string(path, 256);
        int len = ::strlen(path);
        sprintf(path + len, ".log");

        m_file = ::open(
            path,                        // 路径
            O_RDWR | O_APPEND | O_CREAT, // 追加数据
            0666);                       // 其它进程可读
        if (m_file == -1)
            printf("unable to open %s, error = %d\n", path, errno);
    }
    void log(const char *data, size_t size) { ::write(m_file, data, size); }
};

////
// @brief
// 全局logger
//
static Filelog file_log;

void set_ndsl_log_sinks(int sinks, int file_or_ter) // file = 1, ter = 0
{
    if (sinks > 64 || sinks < 0) return;
    if (file_or_ter) {
        tag = 1;
        file_log.init();
    } else {
        tag = 0;
    }
}

void ndsl_log_into_sink(int level, int source, const char *format, ...)
{
    int i = 1;
    ndsl::utils::TimeStamp ts;
    char buffer[4096] = {0};

    ts.now();
    buffer[0] = '[';
    ts.to_string(buffer + 1, 4096);
    int ret1 = ::strlen(buffer);
    buffer[ret1] = ']';

    int ret2 = sprintf(
        buffer + ret1 + 1,
        " lv=%d pid=%d tid=%lx ",
        level,
        ::getpid(),
        (long) ::pthread_self()); // 毫秒

    // 复制数据
    va_list ap;
    va_start(ap, format);
    int ret3 =
        vsnprintf(buffer + ret1 + ret2 + 1, 512 - ret1 - ret2 - 1, format, ap);
    if (ret3 < 0) return;

    if (tag == 0) { std::cout << buffer << std::endl; }
    while ((i <= source) && (tag == 1)) {
        if (source & i) { file_log.log(buffer, ret1 + ret2 + ret3 + 1); }
        i = i * 2;
    }
}
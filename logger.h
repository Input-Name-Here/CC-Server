#include <string.h>

enum LogLevel {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_FATAL
};

class Logger {
public:
    static void Log(LogLevel level, const char* msg);
private:
    static const char* getColor(LogLevel level);
};

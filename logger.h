#include <string.h>
#include <string>
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
    static void sLog(LogLevel level, const std::string msg);
private:
    static const char* getColor(LogLevel level);
};

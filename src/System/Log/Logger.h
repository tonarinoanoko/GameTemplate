#pragma once

#include <iostream>
#include <string>
#include <cstdarg>
#include <ctime>

namespace Log {

enum class eLogLevel {
    Trace,
    Debug,
    Info,
    Warning,
    Error,
    Critical
};

class Logger {
private:
    static Logger* instance;
    Logger();
    ~Logger() = default;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    eLogLevel currentLogLevel;

    std::string getTimestamp() const;
    void logInternal(eLogLevel level, const char* format, va_list args);

public:
    static Logger& getInstance();
    void setLogLevel(eLogLevel level);

    void trace(const char* format, ...);
    void debug(const char* format, ...);
    void info(const char* format, ...);
    void warning(const char* format, ...);
    void error(const char* format, ...);
    void critical(const char* format, ...);

    void assertLog(bool condition, eLogLevel level, const char* format, ...);
};
} // namespace Log

// マクロ定義
#ifdef _DEBUG
#define LOGGER_TRACE(format, ...) (Log::Logger::getInstance().trace(format, __VA_ARGS__))
#define LOGGER_DEBUG(format, ...) (Log::Logger::getInstance().debug(format, __VA_ARGS__))
#else
#define LOGGER_TRACE(format, ...) ((void)0)
#define LOGGER_DEBUG(format, ...) ((void)0)
#endif
#define LOGGER_INFO(format, ...)  (Log::Logger::getInstance().info(format, __VA_ARGS__))
#define LOGGER_WARNING(format, ...) (Log::Logger::getInstance().warning(format, __VA_ARGS__))
#define LOGGER_ERROR(format, ...) (Log::Logger::getInstance().error(format, __VA_ARGS__))
#define LOGGER_CRITICAL(format, ...) (Log::Logger::getInstance().critical(format, __VA_ARGS__))
#define LOGGER_ASSERT(condition, level, format, ...) (Log::Logger::getInstance().assertLog(condition, level, format, __VA_ARGS__))

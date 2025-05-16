#pragma once

#include <iostream>
#include <string>
#include <cstdarg> // 可変長引数
#include <ctime>   // タイムスタンプ

namespace System {
namespace Log {

enum class LogLevel {
    TRACE,
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};

class Logger {
private:
    static Logger* instance;
    Logger();
    ~Logger() = default;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    LogLevel currentLogLevel;

    std::string getTimestamp() const;
    void logInternal(LogLevel level, const char* format, va_list args);

public:
    static Logger& getInstance();
    void setLogLevel(LogLevel level);

    void trace(const char* format, ...);
    void debug(const char* format, ...);
    void info(const char* format, ...);
    void warning(const char* format, ...);
    void error(const char* format, ...);
    void critical(const char* format, ...);

    void assertLog(bool condition, LogLevel level, const char* format, ...);
};

// マクロ定義
#ifdef _DEBUG // デバッグビルドの場合のみ有効にするのが一般的
#define LOGGER_TRACE(format, ...) (System::Log::Logger::getInstance().trace(format, __VA_ARGS__))
#define LOGGER_DEBUG(format, ...) (System::Log::Logger::getInstance().debug(format, __VA_ARGS__))
#else
#define LOGGER_TRACE(format, ...) ((void)0)
#define LOGGER_DEBUG(format, ...) ((void)0)
#endif
#define LOGGER_INFO(format, ...)  (System::Log::Logger::getInstance().info(format, __VA_ARGS__))
#define LOGGER_WARNING(format, ...) (System::Log::Logger::getInstance().warning(format, __VA_ARGS__))
#define LOGGER_ERROR(format, ...) (System::Log::Logger::getInstance().error(format, __VA_ARGS__))
#define LOGGER_CRITICAL(format, ...) (System::Log::Logger::getInstance().critical(format, __VA_ARGS__))
#define LOGGER_ASSERT(condition, level, format, ...) (System::Log::Logger::getInstance().assertLog(condition, level, format, __VA_ARGS__))


} // namespace Log
} // namespace System

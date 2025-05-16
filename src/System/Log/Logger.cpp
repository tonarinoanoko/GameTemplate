#include "System/Log/Logger.h"
#include <cstdio> // vsnprintf

namespace System {
namespace Log {

Logger* Logger::instance = nullptr;

Logger::Logger() : currentLogLevel(LogLevel::DEBUG) {}

Logger& Logger::getInstance() {
    if (!instance) {
        instance = new Logger();
    }
    return *instance;
}

void Logger::setLogLevel(LogLevel level) {
    currentLogLevel = level;
}

std::string Logger::getTimestamp() const {
    std::time_t now = std::time(nullptr);
    std::tm tstruct;
    //localtime_r(&now, &tstruct);
    char buf[80];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tstruct);
    return buf;
}

void Logger::logInternal(LogLevel level, const char* format, va_list args) {
    if (level < currentLogLevel) {
        return;
    }

    const char* levelStr = "";
    switch (level) {
        case LogLevel::TRACE:    levelStr = "[TRACE]"; break;
        case LogLevel::DEBUG:    levelStr = "[DEBUG]"; break;
        case LogLevel::INFO:     levelStr = "[INFO ]"; break;
        case LogLevel::WARNING:  levelStr = "[WARN ]"; break;
        case LogLevel::ERROR:    levelStr = "[ERROR]"; break;
        case LogLevel::CRITICAL: levelStr = "[CRIT ]"; break;
    }

    std::string timestamp = getTimestamp();
    char buffer[1024]; // 適切なサイズを設定
    vsnprintf(buffer, sizeof(buffer), format, args);
    std::cout << timestamp << " " << levelStr << " " << buffer << std::endl;
}

void Logger::trace(const char* format, ...) {
    va_list args;
    va_start(args, format);
    logInternal(LogLevel::TRACE, format, args);
    va_end(args);
}

void Logger::debug(const char* format, ...) {
    va_list args;
    va_start(args, format);
    logInternal(LogLevel::DEBUG, format, args);
    va_end(args);
}

void Logger::info(const char* format, ...) {
    va_list args;
    va_start(args, format);
    logInternal(LogLevel::INFO, format, args);
    va_end(args);
}

void Logger::warning(const char* format, ...) {
    va_list args;
    va_start(args, format);
    logInternal(LogLevel::WARNING, format, args);
    va_end(args);
}

void Logger::error(const char* format, ...) {
    va_list args;
    va_start(args, format);
    logInternal(LogLevel::ERROR, format, args);
    va_end(args);
}

void Logger::critical(const char* format, ...) {
    va_list args;
    va_start(args, format);
    logInternal(LogLevel::CRITICAL, format, args);
    va_end(args);
}

void Logger::assertLog(bool condition, LogLevel level, const char* format, ...) {
    if (!condition) {
        va_list args;
        va_start(args, format);
        logInternal(level, format, args);
        va_end(args);
        // アサート失敗時の処理 (例: std::terminate())
        std::terminate();
    }
}

} // namespace Log
} // namespace System

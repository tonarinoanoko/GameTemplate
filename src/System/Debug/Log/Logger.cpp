#include "System/Debug/Log/Logger.h"
#include <cstdio>
#include <chrono>

namespace Log {

Logger* Logger::instance = nullptr;

Logger::Logger() : currentLogLevel(eLogLevel::Debug) {}

Logger& Logger::getInstance() {
    if (!instance) {
        instance = new Logger();
    }
    return *instance;
}

void Logger::setLogLevel(eLogLevel level) {
    currentLogLevel = level;
}

std::string Logger::getTimestamp() const {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::tm local_tm;
    localtime_s(&local_tm, &now_c); // Windows 向けスレッドセーフ版
    char buf[80];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &local_tm);
    return buf;
}

void Logger::logInternal(eLogLevel level, const char* format, va_list args) {
    if (level < currentLogLevel) {
        return;
    }

    const char* levelStr = "";
    switch (level) {
        case eLogLevel::Trace:    levelStr = "[TRACE]"; break;
        case eLogLevel::Debug:    levelStr = "[DEBUG]"; break;
        case eLogLevel::Info:     levelStr = "[INFO ]"; break;
        case eLogLevel::Warning:  levelStr = "[WARN ]"; break;
        case eLogLevel::Error:    levelStr = "[ERROR]"; break;
        case eLogLevel::Critical: levelStr = "[CRIT ]"; break;
    }

    std::string timestamp = getTimestamp();
    char buffer[1024]; // 適切なサイズを設定
    vsnprintf(buffer, sizeof(buffer), format, args);
    std::cout << timestamp << " " << levelStr << " " << buffer << std::endl;
}

void Logger::trace(const char* format, ...) {
    va_list args;
    va_start(args, format);
    logInternal(eLogLevel::Trace, format, args);
    va_end(args);
}

void Logger::debug(const char* format, ...) {
    va_list args;
    va_start(args, format);
    logInternal(eLogLevel::Debug, format, args);
    va_end(args);
}

void Logger::info(const char* format, ...) {
    va_list args;
    va_start(args, format);
    logInternal(eLogLevel::Info, format, args);
    va_end(args);
}

void Logger::warning(const char* format, ...) {
    va_list args;
    va_start(args, format);
    logInternal(eLogLevel::Warning, format, args);
    va_end(args);
}

void Logger::error(const char* format, ...) {
    va_list args;
    va_start(args, format);
    logInternal(eLogLevel::Error, format, args);
    va_end(args);
}

void Logger::critical(const char* format, ...) {
    va_list args;
    va_start(args, format);
    logInternal(eLogLevel::Critical, format, args);
    va_end(args);
}

void Logger::assertLog(bool condition, eLogLevel level, const char* format, ...) {
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

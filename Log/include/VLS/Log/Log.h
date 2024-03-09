#pragma once

#include <VLS/Log/AbstractLogSink.h>

namespace VLS {
#ifdef __cpp_lib_source_location
void log(
    Log::LogLevel logLevel, const std::string& message,
    const std::source_location& location = std::source_location::current());
void logTrace(const std::string& message, const std::source_location& location =
                                              std::source_location::current());
void logDebug(const std::string& message, const std::source_location& location =
                                              std::source_location::current());
void logInfo(const std::string& message, const std::source_location& location =
                                             std::source_location::current());
void logWarning(
    const std::string& message,
    const std::source_location& location = std::source_location::current());
void logError(const std::string& message, const std::source_location& location =
                                              std::source_location::current());
void logCritical(
    const std::string& message,
    const std::source_location& location = std::source_location::current());
#else
void log(Log::LogLevel logLevel, const std::string& message);
void logTrace(const std::string& message);
void logDebug(const std::string& message);
void logInfo(const std::string& message);
void logWarning(const std::string& message);
void logError(const std::string& message);
void logCritical(const std::string& message);
#endif
}  // namespace VLS

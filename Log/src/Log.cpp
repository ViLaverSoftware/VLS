#include <VLS/Log/Log.h>
#include <VLS/Log/LogHandler.h>

namespace VLS {

#ifdef __cpp_lib_source_location
void log(Log::LogLevel logLevel, const std::string& message,
         const std::source_location location) {
  Log::LogHandler::instance()->log(logLevel, message, location);
}

void logTrace(const std::string& message, const std::source_location location) {
  log(Log::LogLevel::Trace, message, location);
}

void logDebug(const std::string& message, const std::source_location location) {
  log(Log::LogLevel::Debug, message.c_str(), location);
}

void logInfo(const std::string& message, const std::source_location location) {
  log(Log::LogLevel::Info, message.c_str(), location);
}

void logWarning(const std::string& message,
                const std::source_location location) {
  log(Log::LogLevel::Warning, message.c_str(), location);
}

void logError(const std::string& message, const std::source_location location) {
  log(Log::LogLevel::Error, message.c_str(), location);
}

void logCritical(const std::string& message,
                 const std::source_location location) {
  log(Log::LogLevel::Critical, message.c_str(), location);
}

#else

void log(Log::LogLevel logLevel, const std::string& message) {
  Log::LogHandler::instance()->log(logLevel, message);
}

void logTrace(const std::string& message) {
  log(Log::LogLevel::Trace, message);
}

void logDebug(const std::string& message) {
  log(Log::LogLevel::Debug, message);
}

void logInfo(const std::string& message) { log(Log::LogLevel::Info, message); }

void logWarning(const std::string& message) {
  log(Log::LogLevel::Warning, message);
}

void logError(const std::string& message) {
  log(Log::LogLevel::Error, message);
}

void logCritical(const std::string& message) {
  log(Log::LogLevel::Critical, message);
}
#endif
}  // namespace VLS

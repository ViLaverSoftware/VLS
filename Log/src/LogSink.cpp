#include <VLS/Log/LogSink.h>

namespace VLS::Log {

const char* logLevelName(LogLevel value) {
  switch (value) {
    case LogLevel::Trace:
      return "Trace";
    case LogLevel::Debug:
      return "Debug";
    case LogLevel::Info:
      return "Info";
    case LogLevel::Warning:
      return "Warning";
    case LogLevel::Error:
      return "Error";
    case LogLevel::Critical:
      return "Critical";
    default:
      return "Unknown";
  }
}

#ifdef __cpp_lib_source_location
void LogSink::log(LogLevel level, const std::string& message,
                  const std::source_location location) const {
  if (level >= m_filterLogLevel) {
    privateLog(level, message, location);
  }
}
#else
void LogSink::log(LogLevel level, const std::string& message) const {
  if (level >= m_filterLogLevel) {
    privateLog(level, message);
  }
}
#endif

LogLevel LogSink::filterLogLevel() const { return m_filterLogLevel; }

void LogSink::setFilterLogLevel(LogLevel value) { m_filterLogLevel = value; }

}  // namespace VLS::Log

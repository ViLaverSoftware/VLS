#include <VLS/Log/AbstractLogSink.h>

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
void AbstractLogSink::log(LogLevel level, const std::string &message,
                          const std::source_location location) const {
  if (level >= m_minLogLevel) {
    privateLog(level, message, location);
  }
}
#else
void AbstractLogSink::log(LogLevel level, const std::string &message) const {
  if (level >= m_minLogLevel) {
    privateLog(level, message);
  }
}
#endif

LogLevel LogSink::filterLogLevel() const { return m_filterLogLevel; }

void LogSink::setFilterLogLevel(LogLevel value) { m_filterLogLevel = value; }

}  // namespace VLS::Log

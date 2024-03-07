#pragma once

#include <string>

#ifdef __cpp_lib_source_location
#include <source_location>
#endif

namespace VLS::Log {

enum class LogLevel { Trace, Debug, Info, Warning, Error, Critical };

const char* logLevelName(LogLevel value);

class LogSink {
 public:
  virtual ~LogSink() = default;

  virtual std::string name() const = 0;

#ifdef __cpp_lib_source_location
  void log(LogLevel level, const std::string& message,
           const std::source_location location = std::source_location()) const;
#else
  void log(LogLevel level, const std::string& message) const;
#endif

  LogLevel filterLogLevel() const;
  void setFilterLogLevel(LogLevel value);

 protected:
#ifdef __cpp_lib_source_location
  virtual void privateLog(LogLevel level, const std::string& message,
                          const std::source_location location) const = 0;
#else
  virtual void privateLog(LogLevel level, const std::string& message) const = 0;
#endif

  LogLevel m_filterLogLevel = LogLevel::Trace;
};

}  // namespace VLS::Log

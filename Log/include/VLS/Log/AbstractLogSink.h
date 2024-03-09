#pragma once

#include <string>

#ifdef __cpp_lib_source_location
#include <source_location>
#endif

namespace VLS::Log {

enum class LogLevel { Trace, Debug, Info, Warning, Error, Critical };

const char* logLevelName(LogLevel value);


/**
 * @brief The AbstractLogSink class is the abstract base class for VLS logging. It can filter log messages based on the min log level. The default value is Trace wich forwards all log messages.
 * The AbstractLogSink class must be used when a custom log sink is created, but it is also as base class for the LogHandler.
 */
class AbstractLogSink {
 public:
  virtual ~AbstractLogSink() = default;

  virtual std::string name() const = 0;

#ifdef __cpp_lib_source_location
  void log(LogLevel level, const std::string& message,
           const std::source_location location = std::source_location()) const;
#else
  void log(LogLevel level, const std::string& message) const;
#endif

  LogLevel minLogLevel() const;
  void setMinLogLevel(LogLevel value);

 protected:
#ifdef __cpp_lib_source_location
  virtual void privateLog(LogLevel level, const std::string& message,
                          const std::source_location location) const = 0;
#else
  virtual void privateLog(LogLevel level, const std::string& message) const = 0;
#endif

  LogLevel m_minLogLevel = LogLevel::Trace;
};

}  // namespace VLS::Log

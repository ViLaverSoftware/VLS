#pragma once

#include <VLS/Log/LogSink.h>

#include <vector>
#include <mutex>

namespace VLS::Log
{
/**
 * @brief The LogHandler class can redirect logging to one or more log sinks.
 * Log handlers can be nested wich is usefull if different libraries use different log handlers.
 * Most importantly the LogHandler speperate the sometimes complicated implementation of a log sink,
 * from the ability to log. The log will not go anywhere unless a log sink is added to the log handler
 * but that only an advantage. You might not want logging when running unit tests, or you want to also
 * test what is logged.
 *
 * Log events are received though the log(...) function. It is possible to set a minimum log level.
 * All logs with a lower log level will be ignored.
 * Log sinks can be added using the addLogSink(...) class that takes a weak pointer to a log sink.
 * If no log sink is added all logging will be ignored. The log handler will only forward logs to
 * not expired log sinks. Note that log sinks are not kept alive by the LogHandler.
 * All VLS libraries will use the default static LogHandler acessable via the instance() function.
 * Convinience logging functions are exposed by the Log.h file.
 * Log handler is thread safe as all asses to log sinks are protected by a mutex.
 *
 *
 */
class LogHandler : public LogSink
{
public:
  LogHandler();
  /**
  * @brief instance Used by all VLS libraries when logging.
  * @return A shared pointer to make it possible to add this LogHandler to an other LogHandler as a LogSink.
  */
  static std::shared_ptr<LogHandler>& instance();

  /**
   * @brief name All log sinks must have a name. It is only used for error reporting.
   */
  std::string name() const override;

  void addLogSink(std::weak_ptr<LogSink> logSink);

  void clearLogSinks();

protected:
 #ifdef __cpp_lib_source_location
  void privateLog(LogLevel level, const std::string& message, const std::source_location location ) const override;
#else
    void privateLog(LogLevel level, const std::string& message) const override;
#endif

  mutable std::mutex m_sinkMutex;
  std::vector< std::weak_ptr<LogSink> > m_logSinks;
};
}

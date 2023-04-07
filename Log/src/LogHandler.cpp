
#include <VLS/Log/LogHandler.h>

#include <iostream>

namespace VLS::Log {

LogHandler::LogHandler()
  : LogSink()
{}

std::shared_ptr<LogHandler>& LogHandler::instance()
{
  static std::shared_ptr<LogHandler> s_logHandler = std::make_shared<LogHandler>();
  return s_logHandler;
}

std::string LogHandler::name() const
{
  return "LogHandler";
}

void LogHandler::addLogSink(std::weak_ptr<LogSink> logSink)
{
  if (logSink.expired()) {
      return;
  }
  std::scoped_lock< std::mutex > lock( m_sinkMutex );
  m_logSinks.push_back(logSink);
}

void LogHandler::clearLogSinks()
{
  std::scoped_lock< std::mutex > lock( m_sinkMutex );
  m_logSinks.clear();
}

#ifdef __cpp_lib_source_location
void LogHandler::privateLog(LogLevel level, const std::string& message, const std::source_location location ) const
{
  std::scoped_lock< std::mutex > lock( m_sinkMutex );
  for (auto& logSink: m_logSinks)
  {
      auto sharedPtr = logSink.lock();
      if (sharedPtr) {
          try {
              sharedPtr->log(level, message, location);
          } catch (...) {
              std::cerr << "Exception thrown while trying to log to: " << sharedPtr->name();
          }
      }
  }
}
#else
void LogHandler::privateLog(LogLevel level, const std::string& message) const
{
  std::scoped_lock< std::mutex > lock( m_sinkMutex );
  for (auto& logSink: m_logSinks)
  {
    auto sharedPtr = logSink.lock();
    if (sharedPtr) {
      try {
        sharedPtr->log(level, message);
      } catch (...) {
        std::cerr << "Exception thrown while trying to log to: " << sharedPtr->name();
      }
    }
  }
}
#endif

}

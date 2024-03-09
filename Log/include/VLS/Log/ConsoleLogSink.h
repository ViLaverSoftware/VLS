#pragma once

#include <VLS/Log/AbstractLogSink.h>

namespace VLS::Log {
class ConsoleLogSink : public AbstractLogSink {
 public:
  ConsoleLogSink();

  std::string name() const override;

 protected:
#ifdef __cpp_lib_source_location
  void privateLog(LogLevel level, const std::string &message,
                  const std::source_location &location) const override;
#else
  void privateLog(LogLevel level, const std::string& message) const override;
#endif
};
}  // namespace VLS::Log

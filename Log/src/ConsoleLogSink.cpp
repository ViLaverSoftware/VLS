#include <VLS/Log/ConsoleLogSink.h>

#include <iostream>

namespace VLS::Log {

ConsoleLogSink::ConsoleLogSink() {}

std::string ConsoleLogSink::name() const { return "ConsoleLogSink"; }

#ifdef __cpp_lib_source_location
void ConsoleLogSink::privateLog(LogLevel level, const std::string& message,
                                const std::source_location location) const {
  if (level >= LogLevel::Error) {
    std::cerr << message << std::endl;
    //    std::cerr << location.file_name() << "("
    //              << location.line() << ":"
    //              << location.column() << ") `"
    //              << location.function_name() << "`: "
    //              << message << std::endl;
  } else {
    std::cerr << message << std::endl;
    //    std::cout << location.file_name() << "("
    //              << location.line() << ":"
    //              << location.column() << ") `"
    //              << location.function_name() << "`: "
    //              << message << std::endl;
  }
}
#else
void ConsoleLogSink::privateLog(LogLevel level,
                                const std::string& message) const {
  if (level >= LogLevel::Error) {
    std::cerr << message << std::endl;
  } else {
    std::cout << message << std::endl;
  }
}
#endif
}  // namespace VLS::Log

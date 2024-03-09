#include <VLS/Log/ConsoleLogSink.h>

#include <chrono>
#include <format>
#include <iostream>
#include <syncstream>
#include <thread>

namespace VLS::Log {

ConsoleLogSink::ConsoleLogSink() {}

std::string ConsoleLogSink::name() const { return "ConsoleLogSink"; }

#ifdef __cpp_lib_source_location
void ConsoleLogSink::privateLog(LogLevel level, const std::string& message,
                                const std::source_location& location) const {
  std::thread::id this_id = std::this_thread::get_id();
  std::osyncstream synced_stream((level >= LogLevel::Error) ? std::cerr
                                                            : std::cout);
  synced_stream << std::format("{:%Y-%m-%d %H:%M:%OS} |",
                               std::chrono::system_clock::now())
                << this_id
                << std::format("| {}({}, {}): {}", location.file_name(),
                               location.line(), location.column(), message)
                << std::endl;
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

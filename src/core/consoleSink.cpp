#include <iostream>
#include <logger/sinks.hpp>
#include <syncstream>

namespace Logger {
void ConsoleSink::write(const Log &log) {
  std::string logString = log.makeLog();
  std::osyncstream(std::cout) << LevelToEscapeChar(log.logLevel) << logString
                              << colorToEscapeChar(Colors::CLEAR) << '\n';
}
} // namespace Logger

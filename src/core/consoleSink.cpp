#include <iostream>
#include <logger/sinks.hpp>
#include <syncstream>

namespace Logger {
void ConsoleSink::write(const Log &log) {

  std::string result =
      std::format("[{:%Y-%m-%d %H:%M:%S}] [{}] [{}] {}", log.timestamp,
                  levelToString(log.logLevel), log.origin, log.message);
  if (log.hasBinaryData()) {
    result += std::format(" [+ {} bytes of binary data]", log.rawBytes.size());
  }

  std::osyncstream(std::cout) << LevelToEscapeChar(log.logLevel) << result
                              << colorToEscapeChar(Colors::CLEAR) << '\n';
}
} // namespace Logger

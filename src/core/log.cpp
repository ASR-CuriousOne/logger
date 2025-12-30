#include <chrono>
#include <format>
#include <logger/log.hpp>

namespace Logger {

std::string Log::makeLog() const {
  auto currTime = std::chrono::time_point_cast<std::chrono::seconds>(
      std::chrono::system_clock::now());
  return std::format("[{:%Y-%m-%d %H:%M:%S}] [{}] [{}] {}", currTime,
                     levelToString(logLevel), origin, message);
}
} // namespace Logger

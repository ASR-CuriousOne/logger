#pragma once
#include <chrono>
#include <cstdint>
#include <logger/channel.hpp>
#include <logger/common.hpp>
#include <string>
#include <vector>

namespace Logger {
struct Log {
  LogLevel logLevel = LogLevel::INFO;
  std::reference_wrapper<const Channel> channel = General;

  std::chrono::system_clock::time_point timestamp;
  std::string origin;
  std::string message;
  std::vector<uint8_t> rawBytes;

  bool hasBinaryData() const { return !rawBytes.empty(); }
};

} // namespace Logger

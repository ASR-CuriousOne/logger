#pragma once
#include <chrono>
#include <format>
#include <logger/common.hpp>
#include <string>

namespace Logger {
struct Log {
  LogLevel logLevel = LogLevel::INFO;
  std::string origin;
  std::string message;

  std::string makeLog () const;
};
} // namespace Logger

#pragma once
#include <logger/common.hpp>
#include <logger/log.hpp>
#include <logger/sinks.hpp>
#include <logger/utils/queue.hpp>
#include <memory>
#include <source_location>
#include <string>
#include <thread>
#include <vector>

namespace Logger {

struct RoutedSink {
  std::shared_ptr<ILogSink> sink;
  std::vector<std::reference_wrapper<const Channel>> acceptedChannels;
};

class Logger {
public:
  void log(LogLevel level, const std::string &origin,
           const std::string &message, const Channel &channel = General);

  template <typename T>
  void logBinary(LogLevel level,
                 const std::string &origin, const std::string &message,
                 const T &data, const Channel &channel = General) {
    static_assert(std::is_trivially_copyable_v<T>,
                  "Type must be trivially copyable to serialize raw bytes");

    Log logInfo = {.logLevel = level,
                   .channel = channel,
                   .timestamp = std::chrono::system_clock::now(),
                   .origin = origin,
                   .message = message};

    const uint8_t *bytePtr = reinterpret_cast<const uint8_t *>(&data);
    logInfo.rawBytes.assign(bytePtr, bytePtr + sizeof(T));

    m_logQueue.push(std::move(logInfo));
  }

  void setLevel(LogLevel level);

  void addSink(
      std::shared_ptr<ILogSink> sink,
      const std::vector<std::reference_wrapper<const Channel>> &channels = {});

  Logger();

  ~Logger();

  Logger(const Logger &) = delete;
  Logger &operator=(const Logger &) = delete;

  inline void
  debug(const std::string &message, const Channel &channel = General,
        const std::source_location origin = std::source_location::current()) {
    log(LogLevel::DEBUG, origin.function_name(), message, channel);
  }

  inline void
  info(const std::string &message, const Channel &channel = General,
       const std::source_location origin = std::source_location::current()) {
    log(LogLevel::INFO, origin.function_name(), message, channel);
  }

  inline void
  warn(const std::string &message, const Channel &channel = General,
       const std::source_location origin = std::source_location::current()) {
    log(LogLevel::WARNING, origin.function_name(), message, channel);
  }

  inline void
  error(const std::string &message, const Channel &channel = General,
        const std::source_location origin = std::source_location::current()) {
    log(LogLevel::ERROR, origin.function_name(), message, channel);
  }

  inline void
  fatal(const std::string &message, const Channel &channel = General,
        const std::source_location origin = std::source_location::current()) {
    log(LogLevel::FATAL, origin.function_name(), message, channel);
  }

  inline void debug(const std::string &origin, const std::string &message,
                    const Channel &channel = General) {
    log(LogLevel::DEBUG, origin, message,channel);
  }

  inline void info(const std::string &origin, const std::string &message,
                   const Channel &channel = General) {
    log(LogLevel::INFO, origin, message,channel);
  }

  inline void warn(const std::string &origin, const std::string &message,
                   const Channel &channel = General) {
    log(LogLevel::WARNING, origin, message, channel);
  }

  inline void error(const std::string &origin, const std::string &message,
                    const Channel &channel = General) {
    log(LogLevel::ERROR, origin, message, channel);
  }

  inline void fatal(const std::string &origin, const std::string &message,
                    const Channel &channel = General) {
    log(LogLevel::FATAL, origin, message, channel);
  }

private:
  std::atomic<bool> m_isRunning = true;

  LogLevel m_logLevel = LogLevel::DEBUG;

  std::vector<RoutedSink> m_sinks;

  Utils::mutexQueue<Log> m_logQueue;
  std::thread writerThread;

  void writeLogs(const Log &log);

  void writer();
};

} // namespace Logger

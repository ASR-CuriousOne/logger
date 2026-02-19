#include <cassert>
#include <logger/log.hpp>
#include <logger/logger.hpp>
#include <logger/sinks.hpp>
#include <memory>
#include <thread>

namespace Logger {

Logger::Logger() {
  m_isRunning = true;

  addSink(std::make_shared<ConsoleSink>());
  writerThread = std::thread([this] { writer(); });
}

Logger::~Logger() {
  m_isRunning = false;
  assert(writerThread.joinable());
  writerThread.join();
}

void Logger::log(LogLevel level,
                 const std::string &origin, const std::string &message, const Channel& channel) {

  if (level < m_logLevel)
    return;
  Log log = {.logLevel = level,
             .timestamp = std::chrono::system_clock::now(),
             .origin = origin,
             .message = message};
  m_logQueue.push(std::move(log));
}

void Logger::setLevel(LogLevel level) { m_logLevel = level; }

void Logger::writer() {
  while (m_isRunning || !m_logQueue.isEmpty()) {
    Log logToBeWritten;
    if (m_logQueue.waitAndPop(logToBeWritten, std::chrono::milliseconds(50))) {
      writeLogs(logToBeWritten);
    }
  }
}

void Logger::writeLogs(const Log &log) {
  for (const auto &routedSink : m_sinks) {
    bool shouldWrite = false;

    if (routedSink.acceptedChannels.empty()) {
      shouldWrite = true;
    } else {
      for (const auto &ch : routedSink.acceptedChannels) {
        if (ch.get() == log.channel.get()) {
          shouldWrite = true;
          break;
        }
      }
    }

    if (shouldWrite) {
      routedSink.sink->write(log);
    }
  }
}

void Logger::addSink(
    std::shared_ptr<ILogSink> sink,
    const std::vector<std::reference_wrapper<const Channel>> &channels) {
  m_sinks.push_back({sink, channels});
}

} // namespace Logger

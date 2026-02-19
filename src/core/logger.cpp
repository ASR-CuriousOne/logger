#include <cassert>
#include <logger/log.hpp>
#include <logger/logger.hpp>
#include <logger/sinks.hpp>
#include <memory>
#include <thread>

namespace Logger {

Logger::Logger() {
  m_isRunning = true;

  m_sinks.push_back(std::make_shared<ConsoleSink>());
  writerThread = std::thread([this] { writer(); });
}

Logger::~Logger() {
  m_isRunning = false;
  assert(writerThread.joinable());
  writerThread.join();
}

void Logger::log(LogLevel level, const std::string &origin,
                 const std::string &message) {

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
  for (const auto &sink : m_sinks) {
    sink->write(log);
  }
}

void Logger::addSink(std::shared_ptr<ILogSink> sink) {
  m_sinks.push_back(sink);
}

} // namespace Logger

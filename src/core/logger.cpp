#include <cassert>
#include <logger/log.hpp>
#include <logger/logger.hpp>
#include <syncstream>
#include <iostream>
#include <thread>

namespace Logger {

Logger::Logger() {
	m_isRunning = true;

  writerThread = std::thread([this] { writer(); });

}

Logger::~Logger() {
  m_isRunning = false;
	assert(writerThread.joinable());
  writerThread.join();
}

void Logger::log(LogLevel level, const std::string& origin,
                 const std::string& message) {
  Logger &inst = getInstance();

  if (level < inst.m_logLevel)
    return;

  Log log = {.logLevel = level, .origin = origin, .message = message};

  inst.m_logQueue.push(std::move(log));
}

void Logger::setLevel(LogLevel level){
	getInstance().m_logLevel = level;
}

void Logger::writer() {
  while (m_isRunning || !m_logQueue.isEmpty()) {
    Log logToBeWritten;
    if (m_logQueue.waitAndPop(logToBeWritten, std::chrono::milliseconds(50))) {
      writeLogs(std::move(logToBeWritten));
    }
  }
}

void Logger::writeLogs(Log &&log) {
  std::string logString = log.makeLog();

	std::osyncstream(std::cout) << LevelToEscapeChar(log.logLevel) << logString << colorToEscapeChar(Colors::CLEAR) << '\n';
}
void Logger::writeLogs(const Log &log) {
  std::string logString = log.makeLog();
	std::osyncstream(std::cout) << LevelToEscapeChar(log.logLevel) << logString << colorToEscapeChar(Colors::CLEAR) << '\n';
}
} // namespace Logger

#include <logger/common.hpp>

namespace Logger {

std::string_view levelToString(LogLevel level) {
  switch (level) {
  case LogLevel::DEBUG:
    return "DEBUG";
  case LogLevel::INFO:
    return "INFO";
  case LogLevel::WARNING:
    return "WARNING";
  case LogLevel::ERROR:
    return "ERROR";
  case LogLevel::FATAL:
    return "FATAL";
	default: 
		return "UNKNOWN";
  }
}

std::string_view colorToEscapeChar(Colors color){
	switch (color){
		case Logger::Colors::RED:
			return "\033[31m";
		case Logger::Colors::GREEN:
			return "\033[32m";
		case Logger::Colors::YELLOW:
			return "\033[33m";
		case Logger::Colors::BLUE:
			return "\033[34m";
		case Logger::Colors::MAGENTA:
			return "\033[35m";
		case Logger::Colors::CYAN:
			return "\033[36m";
		case Logger::Colors::CLEAR:
			return "\033[0m";
		default: 
			return "\033[0m";
	}
}

Colors LevelToColor(LogLevel level) {
  switch (level) {
  case LogLevel::DEBUG:
    return Colors::BLUE;
  case LogLevel::INFO:
    return Colors::CYAN;
  case LogLevel::WARNING:
    return Colors::YELLOW;
  case LogLevel::ERROR:
    return Colors::RED;
  case LogLevel::FATAL:
    return Colors::MAGENTA;
	default: 
		return Colors::CLEAR;
  }
}

std::string_view LevelToEscapeChar(LogLevel level) {
	return colorToEscapeChar(LevelToColor(level));  
}

} // namespace Logger

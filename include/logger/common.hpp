#pragma once
#include <string_view>

namespace Logger {

enum class LogLevel { DEBUG, INFO, WARNING, ERROR, FATAL };

std::string_view levelToString (LogLevel level);

enum class Colors {RED , GREEN, BLUE, MAGENTA, CYAN, YELLOW, CLEAR};

std::string_view colorToEscapeChar (Colors color);
Colors LevelToColor (LogLevel level);
std::string_view LevelToEscapeChar (LogLevel level);


} // namespace Logger

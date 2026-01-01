#include <gtest/gtest.h>
#include <iostream>
#include <logger/logger.hpp>
#include <string>

TEST(Logger, Initialization) {
  {
    EXPECT_NO_THROW(auto &ref = Logger::Logger::getInstance());
  }
}

TEST(Logger, SameInstance) {
  auto &ref = Logger::Logger::getInstance();
  auto &ref2 = Logger::Logger::getInstance();

  EXPECT_TRUE(&ref == &ref2);
}

TEST(Logger, LoggingTest) {
  EXPECT_NO_THROW(
      Logger::Logger::log(Logger::LogLevel::WARNING, "GTest", "Test log"));
}

TEST(Logger, LevelsTest) {
  auto &inst = Logger::Logger::getInstance();
  inst.setLevel(Logger::LogLevel::DEBUG);

  std::cout << "With Log level DEBUG" << std::endl;

  EXPECT_NO_THROW(inst.log(Logger::LogLevel::INFO, "GTest", "Info Log"));
  EXPECT_NO_THROW(inst.log(Logger::LogLevel::ERROR, "GTest", "Error Log"));

  inst.setLevel(Logger::LogLevel::ERROR);
  std::cout << "With Log Level ERROR" << std::endl;

  EXPECT_NO_THROW(inst.log(Logger::LogLevel::INFO, "GTest", "Info Log"));
  EXPECT_NO_THROW(inst.log(Logger::LogLevel::ERROR, "GTest", "Error Log"));
}

TEST(Logger, ColorTest) {
  auto &inst = Logger::Logger::getInstance();
  inst.setLevel(Logger::LogLevel::DEBUG);

  EXPECT_NO_THROW(inst.log(Logger::LogLevel::DEBUG, "GTest", "Debug Log"));
  EXPECT_NO_THROW(inst.log(Logger::LogLevel::INFO, "GTest", "Info Log"));
  EXPECT_NO_THROW(inst.log(Logger::LogLevel::WARNING, "GTest", "Warning Log"));
  EXPECT_NO_THROW(inst.log(Logger::LogLevel::ERROR, "GTest", "Error Log"));
  EXPECT_NO_THROW(inst.log(Logger::LogLevel::FATAL, "GTest", "Fatal Log"));
}

//TEST(LoggerInteractive, LiveTest) {
//  auto &inst = Logger::Logger::getInstance();
//  inst.setLevel(Logger::LogLevel::DEBUG);
//
//  while (true) {
//    std::string input;
//
//    std::cin >> input;
//
//    if (input == "exit")
//      break;
//    if (input == "setlevel") {
//      std::string level;
//      std::cin >> level;
//
//      if (level == "debug")
//        inst.setLevel(Logger::LogLevel::DEBUG);
//      else if (level == "info")
//        inst.setLevel(Logger::LogLevel::INFO);
//      else if (level == "warn")
//        inst.setLevel(Logger::LogLevel::WARNING);
//      else if (level == "error")
//        inst.setLevel(Logger::LogLevel::ERROR);
//      else if (level == "fatal")
//        inst.setLevel(Logger::LogLevel::FATAL);
//      continue;
//    }
//    if (input == "level") {
//      std::string level, message;
//      std::cin >> level >> message;
//      Logger::LogLevel messLevel;
//      if (level == "debug")
//        messLevel = Logger::LogLevel::DEBUG;
//      else if (level == "info")
//        messLevel = Logger::LogLevel::INFO;
//      else if (level == "warn")
//        messLevel = Logger::LogLevel::WARNING;
//      else if (level == "error")
//        messLevel = Logger::LogLevel::ERROR;
//      else if (level == "fatal")
//        messLevel = Logger::LogLevel::FATAL;
//      EXPECT_NO_THROW(inst.log(messLevel, "GTest", message));
//			continue;
//    }
//    EXPECT_NO_THROW(inst.log(Logger::LogLevel::WARNING, "GTest", input));
//  }
//}

#include <filesystem>
#include <fstream>
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
class CaptureStdout {
  std::stringstream buffer;
  std::streambuf *prevcout;

public:
  CaptureStdout() : prevcout(std::cout.rdbuf(buffer.rdbuf())) {}
  ~CaptureStdout() { std::cout.rdbuf(prevcout); }
  std::string getString() { return buffer.str(); }
};

Logger::Log createTestLog(const std::string &msg) {
  return Logger::Log{.logLevel = Logger::LogLevel::INFO,
                     .origin = "TestOrigin",
                     .message = msg};
}
TEST(SinkTest, ConsoleSink) {
  CaptureStdout capturer;
  Logger::ConsoleSink consoleSink;

  Logger::Log log = createTestLog("Hello Console");

  consoleSink.write(log);

  std::string output = capturer.getString();
  EXPECT_TRUE(output.find("Hello Console") != std::string::npos);
  EXPECT_TRUE(output.find("[INFO]") != std::string::npos);
}

TEST(SinkTest, FileSink) {
  std::filesystem::path testFile = "testLogOutput.txt";

  if (std::filesystem::exists(testFile)) {
    std::filesystem::remove(testFile);
  }

  {
    Logger::FileSink fileSink(testFile);
    Logger::Log log = createTestLog("Hello File");
    fileSink.write(log);
  }

  EXPECT_TRUE(std::filesystem::exists(testFile));

  std::ifstream inFile(testFile);
  std::stringstream buffer;
  buffer << inFile.rdbuf();
  std::string fileContent = buffer.str();

  EXPECT_TRUE(fileContent.find("Hello File") != std::string::npos);
  EXPECT_TRUE(fileContent.find("[INFO]") != std::string::npos);

  if (std::filesystem::exists(testFile)) {
    std::filesystem::remove(testFile);
  }
}

TEST(SinkTest, NetworkSink) {
  auto udpSink = std::make_shared<Logger::NetworkSink>("127.0.0.1", 9000);
  Logger::Logger::addSink(udpSink);

  EXPECT_NO_THROW(Logger::info("This is sent via UDP!"));
  EXPECT_NO_THROW(Logger::info("This too is sent via UDP!"));
}

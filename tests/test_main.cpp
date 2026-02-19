#include "logger/sinks.hpp"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include <iostream>
#include <logger/logger.hpp>
#include <string>

TEST(Logger, Initialization) { EXPECT_NO_THROW(Logger::Logger testLogger;); }

TEST(Logger, LoggingTest) {
  Logger::Logger testLogger;

  EXPECT_NO_THROW(testLogger.log(Logger::LogLevel::ERROR, "GTest", "Test Log"));
}

TEST(Logger, LevelsTest) {
  Logger::Logger testLogger;
  testLogger.setLevel(Logger::LogLevel::DEBUG);

  std::cout << "With Log level DEBUG" << std::endl;

  EXPECT_NO_THROW(testLogger.log(Logger::LogLevel::INFO, "GTest", "Info Log"));
  EXPECT_NO_THROW(
      testLogger.log(Logger::LogLevel::ERROR, "GTest", "Error Log"));

  testLogger.setLevel(Logger::LogLevel::ERROR);
  std::cout << "With Log Level ERROR" << std::endl;

  EXPECT_NO_THROW(testLogger.log(Logger::LogLevel::INFO, "GTest", "Info Log"));
  EXPECT_NO_THROW(
      testLogger.log(Logger::LogLevel::ERROR, "GTest", "Error Log"));
}

TEST(Logger, ColorTest) {
  Logger::Logger testLogger;
  testLogger.setLevel(Logger::LogLevel::DEBUG);

  EXPECT_NO_THROW(
      testLogger.log(Logger::LogLevel::DEBUG, "GTest", "Debug Log"));
  EXPECT_NO_THROW(testLogger.log(Logger::LogLevel::INFO, "GTest", "Info Log"));
  EXPECT_NO_THROW(
      testLogger.log(Logger::LogLevel::WARNING, "GTest", "Warning Log"));
  EXPECT_NO_THROW(
      testLogger.log(Logger::LogLevel::ERROR, "GTest", "Error Log"));
  EXPECT_NO_THROW(
      testLogger.log(Logger::LogLevel::FATAL, "GTest", "Fatal Log"));
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
Logger::Log createBinaryTestLog(const std::string &msg) {
  auto log = Logger::Log{.logLevel = Logger::LogLevel::INFO,
                         .origin = "TestOrigin",
                         .message = msg};

  int number = 10;

  const uint8_t *bytePtr = reinterpret_cast<const uint8_t *>(&number);
  log.rawBytes.insert(log.rawBytes.end(), bytePtr, bytePtr + sizeof(bytePtr));

  return log;
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
  Logger::Logger testLogger;
  auto udpSink = std::make_shared<Logger::NetworkSink>("127.0.0.1", 9000);
  testLogger.addSink(udpSink);

  EXPECT_NO_THROW(testLogger.info("This is sent via UDP!"));
  EXPECT_NO_THROW(testLogger.info("This too is sent via UDP!"));
}

TEST(SinkTest, BinaryFileSink) {
  std::filesystem::path testBinFile = "testBinLogOutput.bin";

  if (std::filesystem::exists(testBinFile)) {
    std::filesystem::remove(testBinFile);
  }

  {
    Logger::BinaryFileSink binaryFileSink(testBinFile);
    Logger::Log log = createBinaryTestLog("Hello File");
    binaryFileSink.write(log);
  }
	
	

}

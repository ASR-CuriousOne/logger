#include <logger/sinks.hpp>

namespace Logger {
FileSink::FileSink(const std::filesystem::path &filePath) {
  m_file.open(filePath, std::ios::app);
}

void FileSink::write(const Log &log) {

  std::string result =
      std::format("[{:%Y-%m-%d %H:%M:%S}] [{}] [{}] {}", log.timestamp,
                  levelToString(log.logLevel), log.origin, log.message);
  if (log.hasBinaryData()) {
    result += std::format(" [+ {} bytes of binary data]", log.rawBytes.size());
  }

  std::lock_guard<std::mutex> lock(m_mutex);
  if (m_file.is_open()) {
    m_file << result << std::endl;
  }
}
} // namespace Logger

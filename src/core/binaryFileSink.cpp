#include <cstdint>
#include <logger/sinks.hpp>

namespace Logger {
BinaryFileSink::BinaryFileSink(const std::filesystem::path &filePath) {
  m_file.open(filePath, std::ios::binary | std::ios::app);
}

void BinaryFileSink::write(const Log &log) {
  std::lock_guard<std::mutex> lock(m_mutex);

  if (!m_file.is_open())
    return;

  auto epoch_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                      log.timestamp.time_since_epoch())
                      .count();
  uint64_t ts = static_cast<uint64_t>(epoch_ms);
  m_file.write(reinterpret_cast<const char *>(&ts), sizeof(ts));

  uint16_t level = static_cast<uint16_t>(log.logLevel);
  m_file.write(reinterpret_cast<const char *>(&level), sizeof(level));

  uint16_t originLen = static_cast<uint16_t>(log.origin.size());
  m_file.write(reinterpret_cast<const char *>(&originLen), sizeof(originLen));
  m_file.write(log.origin.data(), originLen);

  uint32_t msgLen = static_cast<uint32_t>(log.message.size());
  m_file.write(reinterpret_cast<const char *>(&msgLen), sizeof(msgLen));
  m_file.write(log.message.data(), msgLen);

	uint32_t binLen = static_cast<uint32_t>(log.rawBytes.size());
	m_file.write(reinterpret_cast<const char* >(&binLen), sizeof(binLen));
	m_file.write(reinterpret_cast<const char* >(log.rawBytes.data()), binLen);
}
} // namespace Logger

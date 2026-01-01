#include <logger/sinks.hpp>

namespace Logger {
FileSink::FileSink(const std::filesystem::path &filePath) {
  m_file.open(filePath, std::ios::app);
}

void FileSink::write(const Log &log) {
	std::lock_guard<std::mutex> lock(m_mutex);

	if(m_file.is_open()){
		m_file << log.makeLog() << std::endl;
	}
}
} // namespace Logger

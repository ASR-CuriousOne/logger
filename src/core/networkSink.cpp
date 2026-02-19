#include <cstring>
#include <iostream>
#include <logger/sinks.hpp>
#include <sys/socket.h>
#include <unistd.h>

namespace Logger {
NetworkSink::NetworkSink(const std::string &serverIP, int port) {
  m_socketFd = socket(AF_INET, SOCK_DGRAM, 0);

  if (m_socketFd < 0) {
    std::cerr << "Logger: Failed to create UDP socket" << std::endl;
    return;
  }

  std::memset(&m_servAddr, 0, sizeof(m_servAddr));
  m_servAddr.sin_family = AF_INET;
  m_servAddr.sin_port = htons(port);

  if (inet_pton(AF_INET, serverIP.c_str(), &m_servAddr.sin_addr) <= 0) {
    std::cerr << "Logger: Invalid address/ Address not supported" << std::endl;
  }
}

NetworkSink::~NetworkSink() {
  if (m_socketFd >= 0) {
    close(m_socketFd);
  }
}

void NetworkSink::write(const Log &log) {
  if (m_socketFd < 0)
    return;

  std::string message =
      std::format("[{:%Y-%m-%d %H:%M:%S}] [{}] [{}] {}", log.timestamp,
                  levelToString(log.logLevel), log.origin, log.message);
  if (log.hasBinaryData()) {
    message += std::format(" [+ {} bytes of binary data]", log.rawBytes.size());
  }
  ssize_t sent_bytes =
      sendto(m_socketFd, message.c_str(), message.length(), 0,
             (const struct sockaddr *)&m_servAddr, sizeof(m_servAddr));
  if (sent_bytes < 0) {
    std::cerr << "Couldnt Send Log" << '\n';
  }
}

} // namespace Logger

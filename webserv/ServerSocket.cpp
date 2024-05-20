#include "ServerSocket.hpp"

ServerSocket::ServerSocket(int socket_fd) {
  _socket = socket_fd;
  fcntl(_socket, F_SETFL, O_NONBLOCK);
}
ServerSocket::~ServerSocket() {}

std::string& ServerSocket::get_send_buffer() { return (send_buffer); }

void ServerSocket::send_data(const std::string& data) {
  send_buffer = data;
  ssize_t bytes_sent =
      send(_socket, send_buffer.c_str(), send_buffer.size(), 0);
  if (bytes_sent == -1) {
    perror("send error");
    close(_socket);
  } else {
    send_buffer.erase(0, bytes_sent);
  }
}

void ServerSocket::receive_data() {
  char buffer[1024];
  ssize_t bytes_received = recv(_socket, buffer, sizeof(buffer), 0);
  if (bytes_received <= 0) {
    if (bytes_received < 0) perror("recv error");
    close(_socket);
  } else {
    buffer[bytes_received] = '\0';
    /**
     * chunk data end check
     * 0\r\n > 동현이형 코드에서 가져오기
     */
    clients[_socket] += buffer;
    std::cout << "Received: " << clients[_socket] << std::endl;
  }
}

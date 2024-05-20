#pragma once

#include "Socket.hpp"

class ServerSocket : public Socket {
 private:
  ServerSocket(const ServerSocket& rhs);
  ServerSocket& operator=(const ServerSocket& rhs);
  std::string send_buffer;

 public:
  ServerSocket(int socket_fd);
  ~ServerSocket();
  std::map<int, std::string> clients;
  void send_data(const std::string& data);
  std::string& get_send_buffer();
  void clear_send_buffer();
  void receive_data();
};

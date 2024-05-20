#pragma once

#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>
#include <map>
#include <string>

#include "ISocket.hpp"

class Socket : public ISocket {
 protected:
  int _socket;
  struct sockaddr_in _addr;

 public:
  Socket();
  virtual ~Socket();
  void bind_socket();
  void listen_socket(int backlog);
  void create_socket();
  void set_addr(int port);
  int accept_socket();
  void exit_error(const std::string& str);

  void disconnect_client(int client_fd, std::map<int, std::string>& clients);
  int get_socket() const;
  std::map<int, std::string>& get_clients();
};
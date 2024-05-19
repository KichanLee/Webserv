#pragma once

#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <map>
#include <string>

#include "ISocket.hpp"
#include "KQueueEvent.hpp"

class Socket : public ISocket {
 protected:
  int _socket;
  struct sockaddr_in _addr;
  std::map<int, std::string> clients;
  KQueueEvent _kq;

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
  std::map<int, std::string>& get_clients();  // 반환 타입 수정
};

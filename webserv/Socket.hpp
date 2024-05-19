#pragma once

#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <string>

#include "ISocket.hpp"
#include "KQueueEvent.hpp"

class KQueueEvent;

class Socket : public ISocket {
 protected:
  int _socket;
  struct sockaddr_in _addr;
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
  int get_socket() const { return (_socket); }
};
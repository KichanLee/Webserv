#pragma once

#include <arpa/inet.h>
#include <sys/event.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <vector>

class ISocket {
 public:
  virtual ~ISocket() = 0;
  virtual void create_socket() = 0;
  virtual void set_addr(int port) = 0;
  virtual void bind_socket() = 0;
  virtual void listen_socket(int backlog) = 0;
  virtual int accept_socket() = 0;
  virtual void exit_error(const std::string& str) = 0;
  virtual int get_socket() const = 0;
};

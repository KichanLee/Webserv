#pragma once

#include "Socket.hpp"

class ServerSocket : public Socket{

 private:
  ServerSocket(const ServerSocket& rhs);
  ServerSocket& operator=(const ServerSocket& rhs);

 public:
  ServerSocket();
  ~ServerSocket();
  KQueueEvent get_kqueue();
};

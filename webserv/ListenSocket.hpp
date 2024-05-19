#pragma once

#include "Socket.hpp"

class ListenSocket : public Socket {
 private:
  ListenSocket(const ListenSocket &rhs);
  ListenSocket &operator=(const ListenSocket &rhs);

 public:
  ListenSocket();
  ~ListenSocket();
  KQueueEvent get_kqueue();
};
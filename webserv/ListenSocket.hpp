#pragma once

#include "ISocket.hpp"
#include "KQueueEvent.hpp"
#include "ServerSocket.hpp"
#include "Socket.hpp"

#pragma once

#include "KQueueEvent.hpp"
#include "Socket.hpp"

class KQueueEvent;

class ListenSocket : public Socket {
 private:
  KQueueEvent _kq;

 public:
  ListenSocket(int port, int backlog);
  ~ListenSocket();
  void accept_new_client();
  std::map<int, ServerSocket*> _clientSockets;
};

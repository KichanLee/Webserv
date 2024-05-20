#include "ListenSocket.hpp"

ListenSocket::ListenSocket(int port, int backlog) {
  create_socket();
  set_addr(port);
  bind_socket();
  listen_socket(backlog);
  _kq.add_event(get_socket(), EVFILT_READ, EV_ADD, 0, 0, NULL);
  _kq.enroll_polling_events(*this);
}

void ListenSocket::accept_new_client() {
  int client_fd = accept_socket();
  fcntl(client_fd, F_SETFL, O_NONBLOCK);
  ServerSocket* new_client = new ServerSocket(client_fd);
  _clientSockets[client_fd] = new_client;
  _kq.add_event(client_fd, EVFILT_READ, EV_ADD, 0, 0, NULL);
}

ListenSocket::~ListenSocket() {}

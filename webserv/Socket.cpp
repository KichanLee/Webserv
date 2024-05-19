#include "Socket.hpp"

Socket::Socket() : _socket(0) { memset(&_addr, 0, sizeof(_addr)); }
Socket::~Socket() {
  if (_socket > 0) close(_socket);
}
void Socket::create_socket() {
  _socket = socket(AF_INET, SOCK_STREAM, 0);
  if (_socket == -1)
    exit_error("socket() error: " + std::string(strerror(errno)));
}

void Socket::set_addr(int port) {
  _addr.sin_family = AF_INET;
  _addr.sin_addr.s_addr = htonl(INADDR_ANY);
  _addr.sin_port = htons(port);
}

void Socket::bind_socket() {
  if (bind(_socket, (struct sockaddr*)&_addr, sizeof(_addr)) == -1)
    exit_error("bind() error: " + std::string(strerror(errno)));
}

void Socket::listen_socket(int backlog) {
  if (listen(_socket, backlog) == -1)
    exit_error("listen() error: " + std::string(strerror(errno)));
  fcntl(_socket, F_SETFL, O_NONBLOCK);
}

int Socket::accept_socket() {
  struct sockaddr_in client_addr;
  socklen_t client_addr_size = sizeof(client_addr);
  int client_socket =
      accept(_socket, (struct sockaddr*)&client_addr, &client_addr_size);
  if (client_socket == -1) {
    if (errno != EAGAIN && errno != EWOULDBLOCK) {
      exit_error("accept() error: " + std::string(strerror(errno)));
    } else {
      _kq.add_event(client_socket, EVFILT_READ, EV_ADD, 0, 0, NULL);
    }
  }
  return client_socket;
}

void Socket::exit_error(const std::string& str) {
  std::cerr << str << std::endl;
  exit(EXIT_FAILURE);
}
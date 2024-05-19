#include "ListenSocket.cpp"
#include "ServerSocket.hpp"

int main() {
  {
    ListenSocket ls;
    ls.create_socket();
    ls.set_addr(8080);
    ls.bind_socket();
    ls.listen_socket(5);
    ls.accept_socket();
  }
}
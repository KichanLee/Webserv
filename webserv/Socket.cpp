#include "Socket.hpp"

void Socket::initalize(){
    memset(&serv_addr, 0, sizeof(serv_addr));
    _serv_addr.sin_family = AF_INET;
    _serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    _serv_addr.sin_port = htons(8080);
    return (bind(this->_serv_socket, (struct sockaddr*)&(this->serv_addr), sizeof(this->serv_addr)));
}

int Socket::get_serversocket() const;
{
    return (this->_serv_socket);
}

int Socket::get_listensocket() const;
{
    return (this->_listen_socket);
}

int Socket::listen_socket(int socket, int count)
{
    return (listen(socket, count));
}

void Socket::exit_error(const string& str)
{
    std::cerr << str << std::endl;
    exit(EXIT_FAILURE);
}

void Socket::disconnect_socket(int socket_fd, map<int, string>& sockets)
{
    std::cout << "Client disconnected " << socket_fd << std::endl;
    close(socket_fd);
    sockets.erase(socket_fd);
}

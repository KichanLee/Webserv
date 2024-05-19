#include "ServerSocket.hpp"

ServerSocket::ServerSocket() {}
ServerSocket::~ServerSocket() {}

KQueueEvent ServerSocket::get_kqueue() { return (_kq); }
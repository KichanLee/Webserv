#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <map>
#include <vector>

class Socket{
    
    private:
        Socket();
        virtual ~Socket();
        Socket(const Socket& rhs);
        Socket& operator=(const Socket& rhs);
        
        int _listen_socket;
        int _serv_socket;
        struct sockaddr_in _serv_addr;
        
    public:
        int bind_initalize() const;
        int get_serversocket() const;
        void disconnect_socket(int socket_fd, map<int, string>& sockets);
        void exit_error(const string& str);
        int listen_socket(int socket, int count);
        int get_serversocket() const;
        int get_listensocket() const;

};



#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <map>
#include <vector>

#include "Socket.hpp"

class Socket;


class Kqueue{

    private :
        Kqueue();
        virtual ~Kqueue();
        Kqueue(const Kqueue& rhs);
        Kqueue& operator=(const Kqueue& rhs);
        int _kq;
        int _new_events;
        std::map<int, std::string> _clients;
        std::vector<struct kevent> _kqueue_vec;
        struct kevent _event_list[10];
        struct kevent* _curr_event;
        Socket _socket;    
    public :
        void add_kqueue(std::vector<struct kevent>& list, int server_socketfd, uintptr_t ident, int16_t filter, \
        uint16_t flags, uint32_t fflags, intptr_t data, void *udata);
        
        int execute_kevent(int kq, const struct kevent *changelist, int nchanges, struct kevent *eventlist, \
        int nevents, const struct timespec *timeout);
        void exit_with_perror(const std::string& str);

};

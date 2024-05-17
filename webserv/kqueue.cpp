#include <kqueue.hpp>

void Kqueue::exit_with_perror(const std::string& str)
{
    std::cerr << str << std::endl;
    exit(EXIT_FAILURE);
}

void Kqueue::add_kqueue(std::vector<struct kevent>& list, int server_socketfd, uintptr_t ident, int16_t filter, \
        uint16_t flags, uint32_t fflags, intptr_t data, void *udata)
        {
            struct kevent tmp;

            EV_SET(&tmp, ident, filter, flags, fflags, data, udata);
            this->_change_list.push_back(tmp);
        }
        

int Kqueue::execute_kevent(int kq, const struct kevent *changelist, int nchanges, \
struct kevent *eventlist, int nevents, const struct timespec *timeout)
{
    while (1)
    {
        this->_new_events = kevent(kq, changelist, nchanges, event_list, nevents, timeout);
        if(this->_new_events == -1)
            exit_with_perror("kevent() error!\n");
        _kqueue_vec.clear();
        
        for(int i = 0; i < _new_events; ++i)
        {
            curr_event = &event_list[i];

            if(curr_event->flags & EV_ERROR)
            {
                if(curr_event->ident == socket.get_listensocket())
                    exit_with_perror("server socket error\n");
                else
                {
                    std::cerr << "client socket error!\n";
                    disconnect_client(curr_event->ident, clients);
                }
            }
            else if(curr_event->filter == EVFILT_READ)
            {
                if (curr_event->ident == )
            }
        }
    }
}

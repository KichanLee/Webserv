#include "KQueueEvent.hpp"

KQueueEvent::KQueueEvent() {
  _kq = kqueue();
  if (_kq == -1) {
    perror("kqueue create error!\n");
    exit(EXIT_FAILURE);
  }
}

KQueueEvent::~KQueueEvent() { close(_kq); }

void KQueueEvent::add_event(int ident, int16_t filter, uint16_t flags,
                            uint32_t fflags, intptr_t data, void* udata) {
  struct kevent event;
  EV_SET(&event, ident, filter, flags, fflags, data, udata);
  _change_list.push_back(event);
}

int KQueueEvent::wait_for_events(struct kevent* event_list, int max_events,
                                 const struct timespec* timeout) {
  int num_events = kevent(_kq, &_change_list[0], _change_list.size(),
                          event_list, max_events, timeout);
  if (num_events == -1) {
    perror("kevent");
    exit(EXIT_FAILURE);
  }
  _change_list.clear();
  return num_events;
}

void KQueueEvent::enroll_polling_events(Socket& socket) {
  int new_events;
  while (TRUE) {
    /**
     * @brief
     *  kevent function은 인자 kq로 전달된 kqueue에 새로  모니터링할 이벤트 등록
     *  현재 아래 함수에서는 등록만해주고 polling은 해주지 않는다.
     */
    new_events =
        kevent(_kq, &_change_list[0], _change_list.size(), NULL, 0, NULL);
    if (new_events == -1) socket.exit_error("Kevent function error!\n");
    _change_list.clear();
    new_events = kevent(_kq, NULL, 0, _event_list, MAX_EVENTS, NULL);
    if (new_events == -1) socket.exit_error("kevent() polling error!\n");
    process_events(new_events, socket);
  }
}

void KQueueEvent::process_events(int event_cnt, Socket& socket) {
  struct kevent* tmp;

  for (int i = 0; i < event_cnt; ++i) {
    tmp = &_event_list[i];
    error_events(tmp, socket);
    read_events(tmp, socket);
    write_events(tmp, socket);
  }
}

void KQueueEvent::error_events(struct kevent* tmp, Socket& socket) {
  if (tmp->flags & EV_ERROR) {
    if (tmp->ident == socket.get_socket()) {
      socket.exit_error("Listening Socket error!\n");
    } else {
      socket.exit_error("Server Socket error!\n");
    }
  }
}

void KQueueEvent::read_events(struct kevent* tmp, Socket& socket) {
  if (tmp->flags == EVFILT_READ) {
    if (tmp->ident == socket.get_socket()) {
      socket.accept_socket();
    }
  }
}

std::vector<struct kevent> KQueueEvent::get_changeList() {
  return (this->_change_list);
}
struct kevent* KQueueEvent::get_eventList() { return (this->_event_list); }
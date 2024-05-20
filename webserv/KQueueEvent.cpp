#include "KQueueEvent.hpp"

KQueueEvent::KQueueEvent() {
  _kq = kqueue();
  if (_kq == -1) {
    perror("kqueue create error!\n");
    exit(EXIT_FAILURE);
  }
}

KQueueEvent::~KQueueEvent() { close(_kq); }

/**
 * @brief kqueue 추가전, kevent intialize 및 chang_list vector에 추가해준다.
 *
 * @param ident
 * @param filter
 * @param flags
 * @param fflags
 * @param data
 * @param udata
 */
void KQueueEvent::add_event(int ident, int16_t filter, uint16_t flags,
                            uint32_t fflags, intptr_t data, void* udata) {
  struct kevent event;
  EV_SET(&event, ident, filter, flags, fflags, data, udata);
  _change_list.push_back(event);
}

void KQueueEvent::enroll_polling_events(ListenSocket& socket) {
  int new_events;

  // enroll 하고 polling을 따로 해주는것이 의미가 있나?
  while (true) {
    // enrolling event to kqueue
    new_events =
        kevent(_kq, &_change_list[0], _change_list.size(), NULL, 0, NULL);
    if (new_events == -1) socket.exit_error("Kevent() enroll error!\n");
    _change_list.clear();
    // polling event to kqueue
    new_events = kevent(_kq, NULL, 0, _event_list, MAX_EVENTS, NULL);
    if (new_events == -1) socket.exit_error("Kevent() polling error!\n");
    process_events(new_events, socket);
  }
}

void KQueueEvent::process_events(int event_cnt, ListenSocket& socket) {
  struct kevent* tmp;
  for (int i = 0; i < event_cnt; ++i) {
    tmp = &_event_list[i];
    error_events(tmp, socket);
    if (dynamic_cast<ListenSocket*>(&socket)) {
      read_events(tmp, static_cast<ListenSocket&>(socket));
    }
    write_events(tmp, socket);
  }
}

void KQueueEvent::process_events(int event_cnt, ListenSocket& socket) {
  struct kevent* tmp;
  for (int i = 0; i < event_cnt; ++i) {
    tmp = &_event_list[i];
    error_events(tmp, socket);
    read_events(tmp, socket);
    /**
     * @brief  read event 종료 확인하는 함수 추가
     *         이후, write event 등록해주기
     */
    write_events(tmp, socket);
    // timer_events(tmp, socket);
    // proc_events(tmp, socket);
  }
}

void KQueueEvent::error_events(struct kevent* tmp, ListenSocket& socket) {
  if (tmp->flags & EV_ERROR) {
    if (tmp->ident == static_cast<uintptr_t>(socket.get_socket())) {
      socket.exit_error("Listening Socket error!\n");
    } else {
      socket.exit_error("Server Socket error!\n");
    }
  }
}

void KQueueEvent::read_events(struct kevent* tmp, ListenSocket& listen_socket) {
  if (tmp->filter == EVFILT_READ) {
    if (tmp->ident == static_cast<uintptr_t>(listen_socket.get_socket())) {
      listen_socket.accept_new_client();
    } else {
      std::map<int, ServerSocket*>::iterator it =
          listen_socket._clientSockets.find(tmp->ident);
      if (it != listen_socket._clientSockets.end()) {
        ServerSocket* client_socket = it->second;
        client_socket->receive_data();
      }
    }
  }
}

void KQueueEvent::write_events(struct kevent* tmp,
                               ListenSocket& listen_socket) {
  if (tmp->filter == EVFILT_WRITE) {
    std::map<int, ServerSocket*>::iterator it =
        listen_socket._clientSockets.find(tmp->ident);
    if (it != listen_socket._clientSockets.end()) {
      ServerSocket* client_socket = it->second;
      client_socket->send_data(client_socket->get_send_buffer());
    }
  }
}

// CGi 경우 pid 받아서 처리하기
// void KQueueEvent::proc_events(struct kevent* tmp, So
// cket& socket) {
//   if (tmp->filter == EVFILT_PROC) {
//   }
// }

// fork 를 하는 경우에 timer_Events를 등록한다.
// void KQueueEvent::timer_events(struct kevent* tmp, Socket& socket) {
//   int pid;

//   add_event(pid, EVFILT_PROC, EV_ADD, NOTE_EXIT, 0, NULL);
// }

// struct kevent* KQueueEvent::get_eventList() { return _event_list; }

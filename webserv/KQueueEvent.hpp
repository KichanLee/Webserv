#pragma once

#include <fcntl.h>
#include <sys/event.h>
#include <sys/time.h>
#include <unistd.h>

#include <map>

#include "IEvent.hpp"
#include "Socket.hpp"

#define TRUE 1
#define FALSE 1
#define MAX_EVENTS 1024

class Socket;

class KQueueEvent : public IEvent {
 private:
  int _kq;

  std::vector<struct kevent> _change_list;
  struct kevent _event_list[1024];
  /**
   * @brief
   *
   * struct kevent
   * {
   *    key > struct kevent 인스턴스를 가르키는 포인터
   *    ident > 이 이벤트에 대한 식별자, 파일디스크립터, 프로세스아이디
   *    filter > monitoring 중인 이벤트의 유형 (EVFILT_READ, EVFLIT_WRITE,
   ...)
   *    flags > event를 kqueue에 추가 , 수정, 제거하는 방법을 제어하는
   플레그
   * (EV_ADD, EV_ENABLE, EV_DISALBLE, EV_DELETE)
   */

 public:
  KQueueEvent();
  ~KQueueEvent();

  void add_event(int ident, int16_t filter, uint16_t flags, uint32_t fflags,
                 intptr_t data, void* udata);

  int wait_for_events(struct kevent* event_list, int max_events,
                      const struct timespec* timeout);

  void enroll_polling_events(Socket& socket);
  void process_events(int event_cnt, Socket& socket);

  void error_events(struct kevent* tmp, Socket& socket);
  void read_events(struct kevent* tmp, Socket& socket);
  void write_events(struct kevent* tmp, Socket& socket);

  struct kevent* get_eventList();
  std::vector<struct kevent> get_changeList();
};
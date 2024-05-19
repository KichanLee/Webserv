#pragma once

#include <iostream>

class IEvent {
 public:
  virtual ~IEvent();
  virtual void add_event(int ident, int16_t filter, uint16_t flags,
                         uint32_t fflags, intptr_t data, void* udata) = 0;
  virtual int wait_for_events(struct kevent* event_list, int max_events,
                              const struct timespec* timeout) = 0;
};

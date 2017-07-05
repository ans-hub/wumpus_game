// observer.h

#ifndef MVC_SET_OBSERVER_H
#define MVC_SET_OBSERVER_H

namespace mvc_set {

template<class ... T>
struct Observer
{
  Observer() { }
  virtual ~Observer() { }
  Observer(const Observer&) =delete;
  Observer& operator=(const Observer&) =delete;
  virtual bool IncomingNotify(T...) =0;
};

}  // namespace mvc_set

#endif  // MVC_SET_OBSERVER_H
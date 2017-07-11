// observer.h

#ifndef MVC_OBSERVER_H
#define MVC_OBSERVER_H

namespace mvc_set {

template<class...T>
struct Observer
{
  Observer() { }
  virtual ~Observer() { }
  Observer(const Observer&) =delete;
  Observer& operator=(const Observer&) =delete;
  virtual bool IncomingNotify(T...) const =0;
};

}  // namespace mvc_set

#endif  // MVC_OBSERVER_H
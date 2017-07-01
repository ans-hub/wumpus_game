// observable.h

#ifndef MVC_SET_OBSERVABLE_H
#define MVC_SET_OBSERVABLE_H

#include <vector>
#include <algorithm>
#include <functional>

#include "observer.h"

namespace mvc_set {

template<class T, class ... U>
class Observable
{
  std::vector<std::reference_wrapper<Observer<U...>>> controller_;
  std::vector<std::reference_wrapper<Observer<T>>> views_;
public:
  void RegisterView(Observer<T>&);
  void RegisterController(Observer<U...>&);
  void UnregisterView(Observer<T>&);
  void NotifyViews(T) const;
  void RequestController(U ... args) const;
protected:
  Observable() : controller_{ }, views_{ } { }
  // Observable() { }
  Observable(const Observable&) =delete;
  Observable& operator=(const Observable&) =delete;
};

// REALISATION

template<class T, class ... U>
void Observable<T,U...>::RegisterController(Observer<U...>& observer)
{
  if (controller_.empty()) {
    controller_.push_back(observer);
  }
  else {
    controller_[0] = observer;
  }
}

template<class T, class ... U>
void Observable<T,U...>::RegisterView(Observer<T>& observer)
{
  views_.push_back(observer);
}

template<class T, class ... U>
void Observable<T,U...>::UnregisterView(Observer<T>& observer)
{
  views_.erase (
    std::remove (views_.begin(), views_.end(), observer), views_.end()
  );
}

template<class T, class ... U>
void Observable<T,U...>::NotifyViews(T args) const
{
  for (const Observer<T>& observer : views_) {
    // observer->IncomingNotify(std::forward<U>(args)...);
    observer.IncomingNotify(args);
  }
}

template<class T, class ... U>
void Observable<T,U...>::RequestController(U ... args) const
{
  for (const Observer<U...>& observer : controller_) {
    // observer->IncomingNotify(std::forward<U>(args)...);
    observer.IncomingNotify(args...);
  }
}

}  // namespace mvc_set

#endif  // MVC_SET_OBSERVABLE
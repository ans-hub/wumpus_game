// Novoselov Ans @ 2017
// observable.h

#ifndef MVC_OBSERVABLE_H
#define MVC_OBSERVABLE_H

#include <vector>
#include <algorithm>
#include <functional>

#include "observer.h"

namespace mvc_set {

template<class...T>
class Observable
{
  using WrapObserver = std::reference_wrapper<Observer<T...>>;
  std::vector<WrapObserver> observers_;
public:
  void RegisterObserver(Observer<T...>&);
  void UnregisterObserver(Observer<T...>&);
  void NotifyObservers(T...args) const;
protected:
  Observable() : observers_{ } { }
  Observable(const Observable&) =delete;
  Observable& operator=(const Observable&) =delete;
};

template<class...T>
void Observable<T...>::RegisterObserver(Observer<T...>& o)
{
  observers_.push_back(o);
}

template<class...T>
void Observable<T...>::UnregisterObserver(Observer<T...>& o)
{
  observers_.erase (
    std::remove (o->begin(), o->end(), o), o->end()
  );
}

template<class...T>
void Observable<T...>::NotifyObservers(T...args) const
{
  for (const auto& o : observers_) {
    o.get().IncomingNotify(std::forward<T>(args)...);
  }
}

}  // namespace mvc_set

#endif  // MVC_OBSERVABLE
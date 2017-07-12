// controller.h

#ifndef CONTROLLER_H
#define CONTROLLER_H

namespace mvc_set {

struct Controller
{
  Controller() { }
  virtual ~Controller() { }
  Controller(const Controller&) =delete;
  virtual bool RunModel() =0;
};

}  // namespace mvc_set

#endif  // CONTROLLER_H
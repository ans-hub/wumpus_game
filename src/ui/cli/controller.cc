
#include "controller.h"

namespace mvc_set {

bool CliCtrl::IncomingNotify(Message& msg, int& m) const
{
  if (!istream_) { return false; }
  if(istream_ >> m)
  {
    m = 6;
    return true;
  }
  return false;
}

}  // namespace mvc_set
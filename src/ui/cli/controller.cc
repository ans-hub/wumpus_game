
#include "controller.h"

namespace mvc_set {

bool CliController::IncomingNotify(int& n, int& m) const
{
  if (!istream_) { return false; }
  if(istream_ >> n)
  {
    m = 6;
    return true;
  }
  return false;
}

}  // namespace mvc_set
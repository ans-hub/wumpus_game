
#include "controller.h"

namespace mvc_set {

bool CliCtrl::IncomingNotify(Input& msg, int& m)
{
  if (!istream_) { return false; }

  std::string action;
  do {
    if (istream_ >> action >> m) {
      if ((action == "m") || (action == "move")) {
        msg = Input::MOVE;
      }
      else if ((action == "s") || (action == "shot")) {
        msg = Input::SHOT;
      }
      else if ((action == "h") || (action == "help")) {
        msg = Input::HELP;
      }
      else if ((action == "q") || (action == "quit")) {
        msg = Input::QUIT;
      }
      else {
        msg = Input::UNKNOWN;
      }
    }
    else {
      istream_.clear();
      istream_.ignore(10000, '\n');
    }
    return true;
  } while (true);
}

}  // namespace mvc_set
// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: model's `controller` using ostream routines

#ifndef MVCSET_CLI_CTRL
#define MVCSET_CLI_CTRL

#include <istream>

#include "../3rdparty/observer.h"
#include "../events.h"
#include "../logic.h"

namespace mvc_set {

class CliCtrl : public Observer<Input&, int&>
{
public:
  CliCtrl(std::istream& ist) : istream_{ist} { }
  ~CliCtrl() { }
  bool IncomingNotify(Input& msg, int& n) override;
private:
  std::istream& istream_;
};

namespace cli_helpers {

}  // namespace cli_helpers

}  // namespace mvc_set

#endif  // MVCSET_CLI_CTRL
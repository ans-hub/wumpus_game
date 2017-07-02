// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: model's `view` using ostream routines

#ifndef MVCSET_CLI_VIEW
#define MVCSET_CLI_VIEW

#include <ostream>

#include "../abc/observer.h"
#include "../message.h"
#include "../../logic.h"

namespace mvc_set {

struct CliView : public Observer<Message>
{
  typedef wumpus_game::Logic Model;
  CliView(std::ostream& ost, const Model& model)
  : ostream_{ost}
  , model_{model} { }
  ~CliView() { }
  bool IncomingNotify(Message n) const override;
private:
  std::ostream& ostream_;
  const Model& model_;
};

} // namespace mvc_set

#endif // MVCSET_CLI_VIEW
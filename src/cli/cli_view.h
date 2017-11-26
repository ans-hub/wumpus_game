// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: model's `view` using ostream routines

#ifndef CLI_VIEW_H
#define CLI_VIEW_H

#include <ostream>

#include "3rdparty/observer.h"
#include "entities/logic.h"
#include "entities/helpers.h"
#include "enums/enums.h"

namespace wumpus_game {

struct CliView : public mvc_set::Observer<Event>
{ 
  CliView(std::ostream& ost, Logic& model)
    : ostream_{ost}
    , model_{model} { }
  ~CliView() { }
private:
  bool IncomingNotify(Event) override;
  std::ostream& ostream_;
  Logic& model_;
};

namespace cli_helpers {

  void PrintPrompt(std::ostream&);
  void PrintErrorRoom(std::ostream&);
  void PrintErrorActions(std::ostream&);
  void PrintIntro(std::ostream&, const Logic&);
  void PrintShotNoArrows(std::ostream&);
  void PrintShotNotNeighboring(std::ostream&);
  void PrintGameOver(std::ostream&, Subject::ID);
  void PrintFeels(std::ostream&, const Logic&);
  void PrintNeighbors(std::ostream&, const Logic&);
  void PrintMovedBats(std::ostream&);
  void PrintKilledOneWump(std::ostream&);
  void PrintUnknownCommand(std::ostream&);

}  // namespace cli_helpers 

}  // namespace wumpus_game

#endif // CLI_VIEW_H
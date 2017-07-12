// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: model's `view` using ostream routines

#ifndef CLI_VIEW_H
#define CLI_VIEW_H

#include <ostream>

#include "../3rdparty/observer.h"
#include "../events.h"
#include "../logic.h"
#include "../helpers/entities_helpers.h"

namespace wumpus_game {

struct CliView : public mvc_set::Observer<Event>
{ 
  CliView(std::ostream& ost, Logic& model)
    : ostream_{ost}
    , model_{model} { }
  ~CliView() { }
  bool IncomingNotify(Event) const override;
private:
  std::ostream& ostream_;
  Logic& model_;
};

namespace cli_helpers {

  void print_prompt(std::ostream&);
  void print_error_room(std::ostream&);
  void print_error_action(std::ostream&);
  void print_intro(std::ostream&, const Logic&);
  void print_shot_no_arrays(std::ostream&);
  void print_shot_not_neighboring(std::ostream&);
  void print_game_over(std::ostream&, Subject::ID);
  void print_feels(std::ostream&, const Logic&);
  void print_neighbors(std::ostream&, const Logic&);
  void print_moved_bats(std::ostream&);
  void print_killed_one_wump(std::ostream&);
  void print_unknown_command(std::ostream&);

}  // namespace cli_helpers 

}  // namespace wumpus_game

#endif // CLI_VIEW_H
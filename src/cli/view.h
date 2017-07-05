// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: model's `view` using ostream routines

#ifndef MVCSET_CLI_VIEW
#define MVCSET_CLI_VIEW

#include <ostream>

#include "../3rdparty/observer.h"
#include "../events.h"
#include "../logic.h"
#include "../helpers.h"

namespace mvc_set {

struct CliView : public Observer<Show>
{
  typedef wumpus_game::Logic Model;
  typedef wumpus_game::Logic::Person Person;
  
  CliView(std::ostream& ost, Model& model)
    : ostream_{ost}
    , model_{model} { }
  ~CliView() { }
  bool IncomingNotify(Show msg) override;
private:
  std::ostream& ostream_;
  Model& model_;
};

namespace cli_helpers {

  void print_prompt(std::ostream&);
  void print_error_room(std::ostream&);
  void print_error_action(std::ostream&);
  void print_intro(std::ostream&);
  void print_game_over(std::ostream&, CliView::Person);
  void print_feels(std::ostream&, const wumpus_game::Player&);
  void print_neighbors(std::ostream&, const wumpus_game::Logic&);
  void print_moved_bats(std::ostream&);

}  // namespace cli_helpers 

}  // namespace mvc_set

#endif // MVCSET_CLI_VIEW
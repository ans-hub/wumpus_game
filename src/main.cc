// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: main app of wumpus_game

#include <iostream>

#include "logic.h"
#include "gui/gui.h"
#include "cli/view.h"
#include "cli/controller.h"
#include "ai/controller.h"

int main()
{ 
  using namespace wumpus_game;
  using namespace mvc_set;

  Logic model{};
  Gui view{model};
  Gui& ctrl = view;
  // return (Fl::run());
  // CliView view {std::cout, model};
  // CliCtrl ctrl {std::cin};

  model.RegisterView(view);
  model.RegisterController(ctrl);
  model.Run();

  return 0;
}
// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: main app of wumpus_game

#include <iostream>

#include "logic.h"
#include "ui/cli/view.h"
#include "ui/cli/controller.h"

int main()
{ 
  wumpus_game::Logic  model {};
  mvc_set::CliView    view {std::cout, model};
  mvc_set::CliCtrl    ctrl {std::cin};

  model.RegisterView(view);
  model.RegisterController(ctrl);
  model.Run();

  return 0;
}
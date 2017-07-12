// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: windows container for `gui` view and cotroller

#include "windows.h"

namespace wumpus_game {

Windows::Windows() 
  : main_wnd_{ new FormMain() }
  , popup_wnd_{ new FormPopup() }
{ }

Windows::~Windows()
{
  delete main_wnd_;
  delete popup_wnd_;
}


}  // namespace wumpus_game
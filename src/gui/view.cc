// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: model's `view` using gui

#include "view.h"

namespace wumpus_game {

bool GuiView::IncomingNotify(Event msg) const
{
  switch(msg)
  {
    case Event::NEW_LEVEL :
      gui_helpers::show_intro(model_);
      gui_helpers::disable_buttons(gui_);
      gui_helpers::show_level(gui_, model_);
      break;
    case Event::GAME_OVER :
      gui_helpers::enable_buttons(gui_);
      break;
  }
  return true;
}

namespace gui_helpers { 
  
void show_intro(const Logic&) { }
void disable_buttons(Windows&) { }
void show_level(Windows&, const Logic&) { }
void enable_buttons(Windows&) { }

}  // namespace gui_helpers

}  // namespace wumpus_game
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
      gui_helpers::show_level(gui_, model_);
      gui_helpers::show_intro(gui_, model_);
      gui_helpers::disable_buttons(gui_);
      break;
    case Event::GAME_OVER :
      gui_helpers::enable_buttons(gui_);
      break;
  }
  return true;
}

namespace gui_helpers {
  
void show_intro(Windows&, const Logic&) { }

void disable_buttons(Windows& gui)
{
  auto* wnd = gui.main_wnd_;
  wnd->btn_start_->deactivate();
}

void show_level(Windows& gui, const Logic& model)
{
  int level = model.CurrentLevel();
  RoomButton* btn = new RoomButton(0, 20, 20, 20, 20);
  // btn->callback();
  gui.AddWidget(btn);
  gui.Redraw();
}

void enable_buttons(Windows& gui)
{
  auto* wnd = gui.main_wnd_;
  wnd->btn_start_->activate();
}

}  // namespace gui_helpers

}  // namespace wumpus_game
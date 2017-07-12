// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: model's `view` using gui

#ifndef GUI_VIEW_H
#define GUI_VIEW_H

#include "../3rdparty/observer.h"
#include "../events.h"
#include "../logic.h"
#include "windows.h"

namespace wumpus_game {

struct GuiView : public mvc_set::Observer<Event>
{ 
  GuiView(Windows& gui, Logic& model)
    : gui_{gui}
    , model_{model} { }
  ~GuiView() { }
  bool IncomingNotify(Event) const override;
private:
  Windows& gui_;
  Logic& model_;
};

namespace gui_helpers {
  
  void show_intro(const Logic&);
  void disable_buttons(Windows&);
  void show_level(Windows&, const Logic&);
  void enable_buttons(Windows&);

}  // namespace gui_helpers

}  // namespace wumpus_game

#endif //GUI_VIEW_H
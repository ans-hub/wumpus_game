
#ifndef ROOM_BUTTON_H
#define ROOM_BUTTON_H

#include <FL/Fl.H>
#include <FL/Fl_Light_Button.H>

namespace wumpus_game {

struct RoomButton : Fl_Light_Button
{
  RoomButton(int num, int x, int y, int w, int h)
    : Fl_Light_Button(x, y, w, h)
    , num_{num}
    { }
  int num_;
};

}  // namespace wumpus_game

#endif  // ROOM_BUTTON_H
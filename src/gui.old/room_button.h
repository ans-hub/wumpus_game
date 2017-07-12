
#ifndef MVC_SET_ROOM_BTN
#define MVC_SET_ROOM_BTN

#include <FL/Fl.H>
#include <FL/Fl_Light_Button.H>

#include "../logic.h"
#include "../helpers.h"

namespace mvc_set {

struct RoomButton : Fl_Light_Button
{
  RoomButton(int num, int x, int y, int w, int h, wumpus_game::Logic& model)
    : Fl_Light_Button(x, y, w, h)
    , num_{num}
    , model_{model}
    { }
  int handle(int) override;
  
  int num_;
  wumpus_game::Logic& model_;
};

inline int RoomButton::handle(int event)
{
  int curr_room = model_.player_.GetCurrRoomNum();
  switch(event)
  {
    case FL_PUSH :
      if (model_.game_over_cause_ == wumpus_game::Logic::Person::EMPTY) {
        if (wumpus_game::helpers::is_neighboring_rooms(curr_room, num_, model_.cave_)) {
          value(1);
        }
        redraw();
        return 1;
      }
    default :
      return Fl_Widget::handle(event);
  }
}

}  // namespace mvc_set

#endif  // MVC_SET_ROOM_BTN
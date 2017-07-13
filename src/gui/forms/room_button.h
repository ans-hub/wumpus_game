
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
    , visited_{false}
    { }
  int num_; 
  int visited_;
  int handle(int) override;
};

inline int RoomButton::handle(int event)
{
  switch(event)
  {
    // Make unabling to unpress button

    case FL_PUSH :
      value(1);
      redraw();
      do_callback();
      Fl::pushed(nullptr);
      return 1;
    default :
      return Fl_Widget::handle(event);
  }
}

}  // namespace wumpus_game

#endif  // ROOM_BUTTON_H
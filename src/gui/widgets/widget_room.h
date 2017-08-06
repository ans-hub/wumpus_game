// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: control widget represents interactive rooms on game the map

#ifndef WIDGET_ROOM_H
#define WIDGET_ROOM_H

#include <FL/Fl.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Button.H>

namespace wumpus_game {

struct WidgetRoom : Fl_Button
{
  int num_;
  WidgetRoom(int num, int x, int y, int w, int h)
    : Fl_Button(x, y, w, h)
    , num_{num}
    , img_on_{(new Fl_PNG_Image("../src/gui/widgets/img/room_on.png"))}
    , img_off_{(new Fl_PNG_Image("../src/gui/widgets/img/room_off.png"))}
    , img_mark_{(new Fl_PNG_Image("../src/gui/widgets/img/room_mark.png"))}
  {
    this->image(img_on_);
    this->deimage(img_off_);
    this->box(FL_NO_BOX);
  }
  void Deimage(bool d) { d ? this->deimage(img_mark_) : this->deimage(img_off_); }
  ~WidgetRoom() { }

private:
  Fl_PNG_Image* img_on_;
  Fl_PNG_Image* img_off_;
  Fl_PNG_Image* img_mark_;
  int handle(int) override;
};

inline int WidgetRoom::handle(int event)
{
  switch(event)
  {
    case FL_PUSH :
      if (Fl::event_button() == FL_MIDDLE_MOUSE) {
        value( !value() ? 1 : 0 );
        if (value())
          image(img_mark_);
        else 
          image(img_on_);
      }
      do_callback();
      Fl::pushed(nullptr);                
      return Fl_Widget::handle(event);        
    default :
      return Fl_Widget::handle(event);
  }
}

}  // namespace wumpus_game

#endif  // WIDGET_ROOM_H
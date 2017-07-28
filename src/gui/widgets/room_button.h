// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: FLTK widget represents interactive rooms on game the map

#ifndef ROOM_BUTTON_H
#define ROOM_BUTTON_H

#include <FL/Fl.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Button.H>

namespace wumpus_game {

struct RoomButton : Fl_Button
{
  int num_; 
  int visited_;
  Fl_PNG_Image* img_on_;
  Fl_PNG_Image* img_off_;
  Fl_PNG_Image* img_mark_;
  int handle(int) override;

  RoomButton(int num, int x, int y, int w, int h)
    : Fl_Button(x, y, w, h)
    , num_{num}
    , visited_{false}
    , img_on_{(new Fl_PNG_Image("../src/gui/widgets/img/room_on.png"))}
    , img_off_{(new Fl_PNG_Image("../src/gui/widgets/img/room_off.png"))}
    , img_mark_{(new Fl_PNG_Image("../src/gui/widgets/img/room_mark.png"))}
  {
    this->image(img_on_);
    this->deimage(img_off_);
    this->box(FL_NO_BOX);

    // May be delete this all below?
    // this->align(Fl_Align(512));
    // this->color((Fl_Color)36);
    // this->selection_color((Fl_Color)69);
    // this->labeltype(FL_SHADOW_LABEL);
    // this->labelcolor((Fl_Color)94);
  }
  ~RoomButton()
  {
    delete img_on_;
    delete img_off_;
    delete img_mark_;
  }
};

inline int RoomButton::handle(int event)
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
      // redraw();
      do_callback();
      Fl::pushed(nullptr);                
      return Fl_Widget::handle(event);        
    default :
      return Fl_Widget::handle(event);
  }
}

}  // namespace wumpus_game

#endif  // ROOM_BUTTON_H
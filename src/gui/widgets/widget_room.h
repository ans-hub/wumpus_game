// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: control widget represents interactive rooms on game the map

#ifndef WIDGET_ROOM_H
#define WIDGET_ROOM_H

#include <map>

#include <FL/Fl.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Button.H>

#include "gui/images.h"
#include "enums/enums.h"

namespace wumpus_game {

struct WidgetRoom : Fl_Button
{
  using State = RoomState;
  using StateMap = std::map<State,Fl_Image*>;

  WidgetRoom(int num, int level, Images& images, int x, int y, int w, int h)
    : Fl_Button(x, y, w, h)

    , num_{num}
    , level_{level}
    , marked_{value() ? true : false}
    , locked_{false}
    , images_{}
  {
    images_[State::DARK] = images.GetRoomImage(State::DARK, level_);
    images_[State::LIGHT] = images.GetRoomImage(State::LIGHT, level_);
    images_[State::GATE] = images.GetRoomImage(State::GATE, level_);
    images_[State::GUIDE_OPENED] = images.GetRoomImage(State::GUIDE_OPENED, level_);
    images_[State::GUIDE_CLOSED] = images.GetRoomImage(State::GUIDE_CLOSED, level_);

    SetImage(State::DARK);
    SetDeimage(State::GATE); 

    box(FL_NO_BOX);
  }
  int  GetNum() const { return num_; }
  void SetImage(State state) { if (!locked_) image(images_[state]); }
  void SetDeimage(State state) { if (!locked_) deimage(images_[state]); }

  void SwitchOn() { value(1); }
  void SwitchOff() { value(0); }

  void LockImage() { locked_ = true; }
  void UnlockImage() { locked_ = false; }
  bool IsLockedImage() { return locked_; }

private:
  int       num_;
  int       level_;
  bool      marked_;
  bool      locked_;
  StateMap  images_;

  int handle(int) override;
};

// Handle event on widget, used for determine event of middle button.
// Other events such as right and left btn click is deteremine in controller
// by callback function

inline int WidgetRoom::handle(int event)
{
  switch(event)
  {
    case FL_PUSH :
      if (Fl::event_button() == FL_MIDDLE_MOUSE && !locked_) {
        if (marked_)
          SetImage(State::DARK);
        else
          SetImage(State::LIGHT);
        marked_ = !marked_;
      }
      redraw();
      do_callback();
      Fl::pushed(nullptr);
      return Fl_Widget::handle(event);        
    default :
      return Fl_Widget::handle(event);
  }
}

}  // namespace wumpus_game

#endif  // WIDGET_ROOM_H
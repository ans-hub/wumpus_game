// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: control widget represents interactive rooms on game the map

#ifndef WIDGET_ROOM_H
#define WIDGET_ROOM_H

#include <FL/Fl.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Button.H>

#include "gui/images.h"
#include "enums/enums.h"

namespace wumpus_game {

struct WidgetRoom : Fl_Button
{
  WidgetRoom(int num, int level, Images& images, int x, int y, int w, int h)
    : Fl_Button(x, y, w, h)
    , num_{num}
    , level_{level}
    , marked_{value() ? true : false}
    , deimaged_{false}
    , images_{images}
    , img_on_{images_.GetRoomImage(RoomState::ON, level_)}
    , img_off_{images_.GetRoomImage(RoomState::OFF, level_)}
    , img_mark_{images_.GetRoomImage(RoomState::MARK, level_)}
  {
    image(img_on_);
    deimage(img_off_);
    box(FL_NO_BOX);
  }

  void SetDeimage(bool d)
  {
    d ? this->deimage(img_mark_) : this->deimage(img_off_);
    deimaged_ = d;
  }
  
  int  GetNum() const { return num_; }
  bool IsDeimaged() const { return deimaged_; }
  bool IsMarked() const { return marked_; }
  void SetMarked(bool b) { marked_ = b; b ? image(img_mark_) : image(img_on_); }
  bool IsActive() const { return active() ? true : false; }
  void SetActive(bool b) { b ? activate() : deactivate(); }

private:
  int       num_;
  int       level_;
  bool      marked_;
  bool      deimaged_;

  Images&   images_;
  Fl_Image* img_on_;
  Fl_Image* img_off_;
  Fl_Image* img_mark_;
  
  int handle(int) override;
};

inline int WidgetRoom::handle(int event)
{
  switch(event)
  {
    case FL_PUSH :
      if (Fl::event_button() == FL_MIDDLE_MOUSE) {
        if (marked_)
          image(img_on_);
        else
          image(img_mark_);
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
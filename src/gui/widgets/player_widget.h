// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: FLTK widget represents player on the map

#ifndef PLAYER_WIDGET_H
#define PLAYER_WIDGET_H

#include <vector>
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Group.H>

#include "structs/point.h"
#include "structs/trajectory.h"

namespace wumpus_game {

class PlayerWidget : public Fl_Group
{
public:
  PlayerWidget();
  ~PlayerWidget();
  
  void Move(int x, int y);
  void AnimateBegin(int x, int y);
  void AnimateContinue();
  void AnimateFinish();
  void Shot();
  void UnknownAction();
  void ShowFeels(bool, bool, bool);

private:
  Fl_Group* grp_player_;
  Fl_Group* grp_feels_;
  Fl_Box*   box_wumps_;  
  Fl_Box*   box_bats_;  
  Fl_Box*   box_pits_;  
  Fl_PNG_Image* img_stay_;
  Fl_PNG_Image* img_shot_;
  Fl_PNG_Image* img_bats_;  
  Fl_PNG_Image* img_unknown_;
  Fl_PNG_Image* img_dead_wump_;
  Fl_PNG_Image* img_dead_pits_;
  Fl_PNG_Image* img_feels_box_;
  Fl_PNG_Image* img_feels_bats_;
  Fl_PNG_Image* img_feels_pits_;
  Fl_PNG_Image* img_feels_wumps_;
  Trajectory trajectory_;
  
  static void cb_move_bats(void* w)
  {
    auto* p = ((PlayerWidget*)w);
    if (p->trajectory_.Empty()) {
      p->AnimateFinish();
      Fl::remove_timeout(cb_move_bats, w);
    }
    else {
      p->AnimateContinue();
      Fl::repeat_timeout(0.1, cb_move_bats, w);
    }
  }

  static void cb_stop_bats(void* w)
  {
    Fl::remove_timeout(cb_move_bats, w);
  }
};

}  // namespace wumpus_game

#endif  // PLAYER_WIDGET_H
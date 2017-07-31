// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: group widget represents player on the map

#include "widget_player.h"

namespace wumpus_game {

WidgetPlayer::WidgetPlayer()
  : Fl_Group(0, 0, 70, 80)
  // background don`t forget!!!
  , grp_player_{(new Fl_Group(10, 30, 50, 50))}
  , grp_feels_{(new Fl_Group(5, 0, 60, 30))}
  , box_wumps_{(new Fl_Box(15, 1, 15, 15))}
  , box_bats_{(new Fl_Box(30, 1, 15, 15))}
  , box_pits_{(new Fl_Box(45, 1, 15, 15))}
  , img_stay_{(new Fl_PNG_Image("../src/gui/widgets/img/player_stay.png"))}
  , img_shot_{(new Fl_PNG_Image("../src/gui/widgets/img/player_shot.png"))}
  , img_bats_{(new Fl_PNG_Image("../src/gui/widgets/img/player_bats.png"))}  
  , img_kill_wump_{(new Fl_PNG_Image("../src/gui/widgets/img/player_kill_w.png"))}
  , img_unknown_{(new Fl_PNG_Image("../src/gui/widgets/img/unknown_action.png"))}
  , img_dead_wump_{(new Fl_PNG_Image("../src/gui/widgets/img/player_dead_w.png"))}
  , img_dead_pits_{(new Fl_PNG_Image("../src/gui/widgets/img/player_dead_p.png"))}
  , img_feels_box_{(new Fl_PNG_Image("../src/gui/widgets/img/feels_box.png"))}
  , img_feels_bats_{(new Fl_PNG_Image("../src/gui/widgets/img/feels_bats.png"))}
  , img_feels_pits_{(new Fl_PNG_Image("../src/gui/widgets/img/feels_pits.png"))}
  , img_feels_wumps_{(new Fl_PNG_Image("../src/gui/widgets/img/feels_wumps.png"))}
  , trajectory_{}
{
  TuneAppearance();
}

WidgetPlayer::~WidgetPlayer()
{
  delete img_stay_;
  delete img_shot_;
  delete img_bats_;
  delete img_kill_wump_;
  delete img_unknown_;
  delete img_dead_wump_;
  delete img_dead_pits_;
  delete img_feels_box_;
  delete img_feels_bats_;
  delete img_feels_pits_;
  delete img_feels_wumps_;
  delete box_wumps_;
  delete box_bats_;
  delete box_pits_;
  delete grp_feels_;
  delete grp_player_;
}

void WidgetPlayer::DoesMove(int x, int y)
{
  grp_player_->image(img_stay_);
  position(x,y);
  redraw();
}

void WidgetPlayer::DoesShot()
{
  grp_player_->image(img_shot_);
  redraw();
}

void WidgetPlayer::DoesKillWump()
{
  grp_player_->image(img_kill_wump_);
  redraw();
}

void WidgetPlayer::DoesKilledByWump()
{
  grp_player_->image(img_dead_wump_);
  redraw();
}

void WidgetPlayer::DoesKilledByPits()
{
  grp_player_->image(img_dead_pits_);
  redraw();
}

void WidgetPlayer::DoesUnknownAction()
{
  grp_player_->image(img_unknown_);
  redraw();
}

void WidgetPlayer::DoesFeels(bool wump, bool bats, bool pits)
{
  if (wump) 
    box_wumps_->show();
  else
    box_wumps_->hide();
  if (bats)
    box_bats_->show();
  else
    box_bats_->hide();
  if (pits)
    box_pits_->show();
  else
    box_pits_->hide();
  redraw();
}

void WidgetPlayer::AnimateBegin(int x, int y)
{
  if (trajectory_.Empty()) {
    grp_player_->image(img_bats_);
    int steps = 7;    // move in settings
    trajectory_.Set(this->x(), this->y(), x, y, Trajectory::LINE, steps);
    Fl::add_timeout(0.1, cb_move_bats, this);
  }
}

void WidgetPlayer::AnimateContinue()
{
  if (!trajectory_.Empty()) {
    int x = trajectory_.Next().x_;
    int y = trajectory_.Next().y_;
    trajectory_.Pop();
    position(x, y);
    
    redraw();
    parent()->parent()->redraw();
  }
}

void WidgetPlayer::AnimateFinish()
{
  if (trajectory_.Empty()) {
    trajectory_.Reset();
    grp_player_->image(img_stay_);
    
    redraw();
    parent()->parent()->redraw();
  }
}

// PRIVATE REALISATION

void WidgetPlayer::TuneAppearance()
{
  begin();
  box(FL_BORDER_BOX);
  resizable(0);
  grp_player_->box(FL_BORDER_BOX);
  grp_player_->align(Fl_Align(513));
  grp_feels_->box(FL_BORDER_BOX);
  grp_feels_->align(Fl_Align(513));
  grp_player_->image(img_stay_);
  box_wumps_->image(img_feels_wumps_);
  box_bats_->image(img_feels_bats_);
  box_pits_->image(img_feels_pits_);
  grp_feels_->image(img_feels_box_);
  grp_feels_->add(box_wumps_);
  grp_feels_->add(box_bats_);
  grp_feels_->add(box_pits_);
  grp_feels_->end();
  add(grp_player_);
  add(grp_feels_);
  end();
}

// CALLBACKS SECTION

void WidgetPlayer::cb_move_bats(void* w)
{
  auto* p = ((WidgetPlayer*)w);
  if (p->trajectory_.Empty()) {
    p->AnimateFinish();
    Fl::remove_timeout(cb_move_bats, w);
  }
  else {
    p->AnimateContinue();
    Fl::repeat_timeout(0.1, cb_move_bats, w);
  }
}

void WidgetPlayer::cb_stop_bats(void* w)
{
  Fl::remove_timeout(cb_move_bats, w);
}

}  // namespace wumpus_game
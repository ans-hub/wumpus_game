// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: group widget represents player on the map

#include "widget_player.h"

namespace wumpus_game {

WidgetPlayer::WidgetPlayer()
  : Fl_Group{0, 0, 60, 70}
  , box_player_{(new Fl_Box((w() - 32) / 2, (h() + 10 - 32) / 2, 32, 32))}
  , box_wumps_{(new Fl_Box(20, 0, 20, 20))}
  , box_bats_{(new Fl_Box(40, 0, 20, 20))}
  , box_pits_{(new Fl_Box(0, 0, 20, 20))}
  , img_bg_{(new Fl_PNG_Image("../src/gui/widgets/img/player_bg.png"))}  
  , img_stay_{(new Fl_PNG_Image("../src/gui/widgets/img/player_stay.png"))}
  , img_shot_{(new Fl_PNG_Image("../src/gui/widgets/img/player_shot.png"))}
  , img_walk_{(new Fl_PNG_Image("../src/gui/widgets/img/player_walk.png"))}
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
  end();
}

void WidgetPlayer::SetStateImage(State state)
{
  switch (state) {
    case MOVED_BATS : box_player_->image(img_bats_); break;
    case STAY : box_player_->image(img_stay_); break;
    case WALK : box_player_->image(img_walk_); break;
    case SHOT : box_player_->image(img_shot_); break;
    case KILLED_BY_WUMP : box_player_->image(img_dead_wump_); break;
    case KILLED_BY_PITS : box_player_->image(img_dead_pits_); break;
    case KILL_WUMP : box_player_->image(img_kill_wump_); break;
    case UNKNOWN_ACTION : box_player_->image(img_unknown_); break;    
    default : break;
  }
  redraw();
}

void WidgetPlayer::StaticMove(const Point& to)
{
  position(to.x_, to.y_);
  redraw();
}

void WidgetPlayer::ShowFeelsIcons(bool wump, bool bats, bool pits)
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

void WidgetPlayer::AnimateMove(const Point& to, Trajectory::Type type)
{
  double from_x = static_cast<double>(x());
  double from_y = static_cast<double>(y());
  
  auto step = draw_consts::animation_step;
  auto speed = draw_consts::animation_speed;

  trajectory_.Set(Point{from_x, from_y}, to, type, step);
  Fl::add_timeout(speed, cb_animate_move, this);
}

void WidgetPlayer::AnimateMoveContinue()
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

void WidgetPlayer::AnimateMoveFinish()
{
  SetStateImage(STAY);

  redraw();
  parent()->parent()->redraw();
}

// PRIVATE REALISATION

void WidgetPlayer::TuneAppearance()
{
  this->image(img_bg_);
  this->align(Fl_Align(513));
  this->resizable(0);
  box_player_->align(Fl_Align(513));
  box_player_->image(img_stay_);
  box_wumps_->image(img_feels_wumps_);
  box_bats_->image(img_feels_bats_);
  box_pits_->image(img_feels_pits_);
}

// CALLBACKS SECTION

void WidgetPlayer::cb_animate_move(void* w)
{
  auto* p = ((WidgetPlayer*)w);
  if (!p->IsAnimateInProgress()) {
    p->AnimateMoveFinish();    
    Fl::remove_timeout(cb_animate_move, w); //  we can do this only here :(
  }
  else { 
    p->AnimateMoveContinue();
    auto speed = draw_consts::animation_speed;
    Fl::repeat_timeout(speed, cb_animate_move, w);   // 0.007 is the best
  }
}

}  // namespace wumpus_game
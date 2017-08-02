// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: group widget represents player on the map

#include "widget_player.h"

namespace wumpus_game {

WidgetPlayer::WidgetPlayer()
  : Fl_Group{0, 0, 70, 80}
  , grp_player_{(new Fl_Group(10, 30, 50, 50))}
  , grp_feels_{(new Fl_Group(5, 0, 60, 30))}
  , box_wumps_{(new Fl_Box(15, 1, 15, 15))}
  , box_bats_{(new Fl_Box(30, 1, 15, 15))}
  , box_pits_{(new Fl_Box(45, 1, 15, 15))}
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
}

void WidgetPlayer::SetStateImage(State state)
{
  switch (state) {
    case MOVED_BATS : grp_player_->image(img_bats_); break;
    case STAY : grp_player_->image(img_stay_); break;
    case WALK : grp_player_->image(img_walk_); break;
    case SHOT : grp_player_->image(img_shot_); break;
    case KILLED_BY_WUMP : grp_player_->image(img_dead_wump_); break;
    case KILLED_BY_PITS : grp_player_->image(img_dead_pits_); break;
    case KILL_WUMP : grp_player_->image(img_kill_wump_); break;
    case UNKNOWN_ACTION : grp_player_->image(img_unknown_); break;    
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
  Point from {
    static_cast<double>(this->x()),
    static_cast<double>(this->y())
  };

  auto step = draw_consts::animation_step;
  auto speed = draw_consts::animation_speed;

  trajectory_.Set(from, to, type, step);
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
  begin();
  box(FL_BORDER_BOX);
  this->resizable(0);
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
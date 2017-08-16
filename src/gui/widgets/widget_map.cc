// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: group widget represents map for main window

#include "widget_map.h"

namespace wumpus_game {

WidgetMap::WidgetMap(AudioOut& audio, Images& images)
  : Fl_Group{30, 90, 600, 600}
  , wdg_info_  {new WidgetInfo(images)}
  , wdg_rooms_ {}
  , wdg_player_{new WidgetPlayer(audio, images)}
  , wdg_pathes_{new WidgetNetdraw()}
  , trajectory_{}
  , level_{-1}
  , ready_{true}
  , images_{images}
{
  TuneAppearance();
  end();
}

// INTERFACE REALISATION

// Redraw all children in special order in depends of current level

void WidgetMap::Redraw(int level)
{
  level_ = level;
  begin();
  
  ResizeGroup(level_);
  ChangeLinesParams(level_);
  RedrawLines(level_);
  RecreateRooms(level_);

  wdg_player_->Redraw(level_);
  RefreshPlayerPos();
  wdg_info_->Redraw(level_);
  helpers::MakeTop(wdg_player_, this);
  
  end();
  SetRotateCallback();
}

// Simple changes position of player widget

void WidgetMap::MovePlayerInstantly(int to_room)
{
  this->ready_ = false;
  
  Point to = GetRoomCoords(to_room) - helpers::GetOffset(wdg_player_);
  wdg_player_->SetCurrRoom(to_room);
  wdg_player_->position(to.x_, to.y_);
  
  this->ready_ = true; 
}
 
// Just sets non-ready status, room destination and timeout callback,
// which make all main work

void WidgetMap::MovePlayerAnimated(int to_room)
{
  this->ready_ = false;

  wdg_player_->SetCurrRoom(to_room);  // needs to track and rebuild trajectory

  Fl::add_timeout(
    config::GetPlayerAnimationSpeed(level_),
    cb_move_player_animated, this
  );
}

// Activate all control elements on the widget

void WidgetMap::Activate() {
  for (auto& r : wdg_rooms_)  
    r->activate();
}

// Deactivate all control elements on the widget

void WidgetMap::Deactivate(bool b)
{
  for (auto& r : wdg_rooms_) {
    r->UseDefaultDeimage(b);
    r->deactivate();
  }
}

// Returns current coordinates of room

Point WidgetMap::GetRoomCoords(int room) const
{
  Point res{};
  res.x_ = wdg_pathes_->x() + wdg_pathes_->GetVertexes()[room].x_;
  res.y_ = wdg_pathes_->y() + wdg_pathes_->GetVertexes()[room].y_;
  return res;
}

// REALISATION DETAILS

// Resizes this group depends on width needs to place all level draw

void WidgetMap::ResizeGroup(int level)
{
  int w = config::GetLevelWidth(level);
  resize(30, 90, w, w);
}

// Creates rooms, place its on the widget, and sets callbacks, early
// applied by controller

void WidgetMap::RecreateRooms(int level)
{
  wdg_rooms_.clear();
  int btn_size = config::room_btn_size;
  int rooms = config::GetRoomsCount(level);
  
  for (int i = 0; i < rooms; ++i) {
    Point coords = GetRoomCoords(i);
    auto btn = std::make_unique<WidgetRoom>(
      i,
      level_,
      images_,
      coords.x_ - btn_size / 2,
      coords.y_ - btn_size / 2,
      btn_size,
      btn_size
    );

    btn->callback((Fl_Callback*)this->callback_, this->command_);
    
    wdg_rooms_.push_back(std::move(btn));
  }
}

// Changes position of the rooms when map is have been rotates

void WidgetMap::RepositionRooms()
{
  int i{0};
  int btn_size = config::room_btn_size;
  
  for (auto& r : wdg_rooms_) {
    Point coords = GetRoomCoords(i);
    r->position(
      coords.x_ - btn_size / 2,
      coords.y_ - btn_size / 2
    );
    ++i;
  }
}

// Redraw player widget in depends of current room coordinates. Usually used
// when room coordinates are changed, but player is in other place

void WidgetMap::RefreshPlayerPos()
{
  if (ready_)
    MovePlayerInstantly(wdg_player_->GetCurrRoom());
}

// Redraw WidgetNetdraw in depends of current level

void WidgetMap::RedrawLines(int level)
{
  wdg_pathes_->Redraw(level);
  wdg_pathes_->position(x(), y());
}

// Changes WidgetNetdraw parameters before next redrawing

void WidgetMap::ChangeLinesParams(int level)
{ 
  auto& params = wdg_pathes_->GetParamsReference();
  config::ChangeNetdrawParams(params, level);
}

// SERVICE FUNCTION REALISATION

void WidgetMap::TuneAppearance()
{
  resizable(0);                 // forbid children resizing
  box(FL_PLASTIC_UP_FRAME);
}

// Do next step in animation and rebuild trajectory coordinates in 
// depends of current coordinates of destination room (if it rotate)

void WidgetMap::cb_move_player_animated(void* w)
{
  auto* this_ = ((WidgetMap*)w);

  this_->RefreshAnimateTrajectory();
  Point curr = this_->trajectory_.Next();
  this_->trajectory_.Pop();
  this_->wdg_player_->position(curr.x_, curr.y_);

  if (this_->trajectory_.Empty()) {
    Fl::remove_timeout(cb_move_player_animated, w);
    this_->wdg_player_->SetDefaultState();
    this_->ready_ = true;
  }
  else {
    Fl::repeat_timeout(
      config::GetPlayerAnimationSpeed(this_->level_),    
      cb_move_player_animated, w
    );
  }

  this_->redraw();
  this_->parent()->redraw();
}

// Evaluate movement trajectory if player widget in depends of current
// coordinates of current coordinates and destination

void WidgetMap::RefreshAnimateTrajectory()
{
  int room = wdg_player_->GetCurrRoom();

  Point to = GetRoomCoords(room) - helpers::GetOffset(wdg_player_);
  Point from (wdg_player_->x(), wdg_player_->y());
  
  trajectory_.Set(from, to, Trajectory::LINE, config::animation_step);
}

// Simple set again repeat timeout and call special redrawing member function

void WidgetMap::cb_rotate_map(void* w)
{
  int level = ((WidgetMap*)w)->level_;
  double speed = config::GetRotateMapSpeed(level);  
  
  ((WidgetMap*)w)->RedrawCurrentByRotate();
  Fl::repeat_timeout(speed, cb_rotate_map, w);
}

// Sets rotate callback. Usually used every time WidgetMap id redrawn to
// new level

void WidgetMap::SetRotateCallback()
{
  Fl::remove_timeout(cb_rotate_map, this);    // remove old if present
  
  double speed = config::GetRotateMapSpeed(level_);
  if (speed)
    Fl::add_timeout(speed, cb_rotate_map, this);
}

// Function called by callback

void WidgetMap::RedrawCurrentByRotate()
{
  ChangeLinesParams(level_);
  RedrawLines(level_);
  RepositionRooms();
  RefreshPlayerPos();
  
  helpers::MakeTop(wdg_player_, this);
  helpers::MakeTop(wdg_info_, this);
  
  parent()->redraw();
}

namespace helpers {

Point GetOffset(Fl_Widget* w)
{
  return {w->w() / 2, w->h() / 2};
}

void MakeTop(Fl_Widget* w, Fl_Group* surface)
{
  surface->remove(w);
  surface->add(w);

}

}  // namespace helpers

}  // namespace wumpus_game
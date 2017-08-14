// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: group widget represents map for main window

#include "widget_map.h"

namespace wumpus_game {

WidgetMap::WidgetMap(AudioOut& audio, Images& images)
  : Fl_Group{30, 90, 600, 600}    // here was a bug when parent()->w()...h()
  , wdg_info_  {new WidgetInfo(images)}
  , wdg_rooms_ {}    // make WidgetRooms consists of WidgetRoom* elements
  , wdg_player_{new WidgetPlayer(audio, images)}
  , wdg_pathes_{new WidgetNetdraw()}
  , trajectory_{}
  , rooms_state_{}
  , level_{-1}
  , ready_{true}
  , images_{images} // if wdg_rooms_ be a widget, this would be not necessary
{
  TuneAppearance();
  end();
} 

WidgetMap::~WidgetMap()
{
  for (auto& v : wdg_rooms_) {
    this->remove(v);
    delete v;
  }
}

Point WidgetMap::GetRoomCoords(int room) const
{
  Point res{};
  res.x_ = wdg_pathes_->x() + wdg_pathes_->GetVertexes()[room].x_;
  res.y_ = wdg_pathes_->y() + wdg_pathes_->GetVertexes()[room].y_;
  return res;
}

void WidgetMap::Redraw(int level)
{
  level_ = level;
  begin();
  ResizeGroup(level);
  ClearRooms();
  SetLinesAngles(level);
  DrawLines(level);
  DrawRooms(level);
  wdg_player_->Redraw(level);
  DrawPlayer();
  SetRotateCallback();
  SetRoomsCallback();
  wdg_info_->Redraw(level);
  end();
}

void WidgetMap::MovePlayerInstantly(int to_room)
{
  this->ready_ = false;
  
  Point to = GetRoomCoords(to_room) - helpers::get_offset(wdg_player_);
  wdg_player_->SetCurrRoom(to_room);
  wdg_player_->position(to.x_, to.y_);
  
  // redraw();                 // when rotate - is this is not overhead?
  this->ready_ = true; 
}
 
void WidgetMap::MovePlayerAnimated(int to_room)
{
  this->ready_ = false;
  wdg_player_->SetCurrRoom(to_room);

  Fl::add_timeout(
    config::GetPlayerAnimationSpeed(level_),
    cb_move_player_animated, this
  );
}

void WidgetMap::RefreshAnimateTrajectory()
{
  int room = wdg_player_->GetCurrRoom();

  Point to = GetRoomCoords(room) - helpers::get_offset(wdg_player_);
  Point from (wdg_player_->x(), wdg_player_->y());
  
  trajectory_.Set(from, to, Trajectory::LINE, config::animation_step);
}

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

void WidgetMap::SaveRoomsState()
{
  rooms_state_.clear();

  for (const auto& w : wdg_rooms_ ) {
    auto t = std::make_tuple(
      w->IsMarked(), 
      w->IsActive(), 
      w->IsDeimaged()
    );
    rooms_state_.push_back(t);
  }
}

void WidgetMap::LoadRoomsState()
{
  for (std::size_t i = 0; i < wdg_rooms_.size(); ++i) {
    wdg_rooms_[i]->SetMarked(std::get<0>(rooms_state_[i]));
    wdg_rooms_[i]->SetActive(std::get<1>(rooms_state_[i]));
    wdg_rooms_[i]->SetDeimage(std::get<2>(rooms_state_[i]));
  }  
}

void WidgetMap::RedrawCurrentByRotate()
{
  SaveRoomsState();    
  // ClearRooms();
  SetLinesAngles(level_);
  DrawLines(level_);
  RepositionRooms();  // may be make reposition of rooms??
  LoadRoomsState();
  SetRoomsCallback();
  DrawPlayer();
  remove(wdg_info_);
  add(wdg_info_);
  // wdg_info_->redraw();

  parent()->redraw();
}

void WidgetMap::SetLinesAngles(int level)
{ 
  auto& params = wdg_pathes_->GetParamsReference();
  config::ChangeNetdrawParams(params, level);
}

void WidgetMap::Deactivate(bool d)
{
  for (auto& r : wdg_rooms_) {
    r->SetDeimage(d);
    r->deactivate();
  }
}

void WidgetMap::Activate() {
  for (auto& r : wdg_rooms_)  
    r->activate();
}

// REALISATION DETAILS

void WidgetMap::ResizeGroup(int level)
{
  int w = config::GetLevelWidth(level);
  resize(30, 90, w, w);
}

void WidgetMap::DrawPlayer()
{
  if (ready_) MovePlayerInstantly(wdg_player_->GetCurrRoom());
  remove(wdg_player_);    // needs for top level of wdg_player_
  add(wdg_player_);
}

void WidgetMap::DrawLines(int level)
{
  wdg_pathes_->Redraw(level);
  wdg_pathes_->position(x(), y());
}

void WidgetMap::DrawRooms(int level)
{
  int btn_size = config::room_btn_size;
  int rooms = config::GetVertexesCount(level);
  
  for (int i = 0; i < rooms; ++i) {
    Point coords = GetRoomCoords(i);
    WidgetRoom* btn = new WidgetRoom(
      i,
      level_,
      images_,
      coords.x_ - btn_size / 2,
      coords.y_ - btn_size / 2,
      btn_size,
      btn_size);
    this->add(btn);
    wdg_rooms_.push_back(btn);
  }
}

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
    remove(r);
    add(r);
    redraw();
    ++i;
  }
}

void WidgetMap::ClearRooms()
{
  for (auto& v : wdg_rooms_) {
    remove(v);
    delete v;
  }
  wdg_rooms_.clear();
  wdg_rooms_.resize(0);
}

void WidgetMap::SetRotateCallback()
{
  double speed = config::GetRotateMapSpeed(level_);
  Fl::remove_timeout(cb_rotate_map, this);    // remove old if present
  if (speed)
    Fl::add_timeout(speed, cb_rotate_map, this);
}

void WidgetMap::SetRoomsCallback()
{
  for (auto& b : wdg_rooms_) {
    b->callback((Fl_Callback*)this->callback_, this->command_);
  }  
}

void WidgetMap::TuneAppearance()
{
  resizable(0); // forbid resize children
  box(FL_PLASTIC_UP_FRAME);
}

void WidgetMap::cb_rotate_map(void* w)
{
  int level = ((WidgetMap*)w)->level_;
  double speed = config::GetRotateMapSpeed(level);  
  
  ((WidgetMap*)w)->RedrawCurrentByRotate();
  Fl::repeat_timeout(speed, cb_rotate_map, w);
}

namespace helpers {

Point get_offset(Fl_Widget* w)
{
  return {w->w() / 2, w->h() / 2};
}

}  // namespace helpers

}  // namespace wumpus_game
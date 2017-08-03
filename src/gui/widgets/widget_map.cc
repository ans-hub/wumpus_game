// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: group widget represents map for main window

#include "widget_map.h"

namespace wumpus_game {

WidgetMap::WidgetMap ()
  // : Fl_Group{30, 90, parent()->w(), parent()->h()}
  : Fl_Group{30, 90, 600, 600}    // here was a bug when parent()->w()...h()
  , rooms_{}
  , pathes_{new WidgetNetdraw(1)}
  , player_{new WidgetPlayer()}
{
  TuneAppearance();
  end();
} 

WidgetMap::~WidgetMap()
{
  for (auto& v : rooms_) {
    this->remove(v);
    delete v;
  }
  // remove(player_);
  // delete player_;
}

int WidgetMap::GetRoomCoordX(int num) const
{
  return pathes_->x() + pathes_->GetVertexes()[num].x_;
}

int WidgetMap::GetRoomCoordY(int num) const
{
  return pathes_->y() + pathes_->GetVertexes()[num].y_;
}

void WidgetMap::Redraw(int level)
{
  begin();
  ResizeGroup(level);
  ClearRooms();
  ClearPlayer();
  ClearLines();
  DrawLines(level);
  DrawRooms(level);
  DrawPlayer();
  SetCallbacks();
  end();
}

// REALISATION DETAILS

void WidgetMap::ResizeGroup(int level)
{
  int w = draw_consts::level_width(level);
  this->resize(30, 90, w, w);
}

void WidgetMap::DrawPlayer()
{
  remove(player_);    // needs for top level
  add(player_);
}

void WidgetMap::DrawLines(int level)
{
  // pathes_ = new WidgetNetdraw(level);
  // add(pathes_);
  pathes_->Redraw(level);
  pathes_->position(x(), y());
}

void WidgetMap::DrawRooms(int level)
{
  int btn_size = draw_consts::room_btn_size;
  int rooms = draw_consts::level_vertexes(level);
  
  for (int i = 0; i < rooms; ++i) {
    WidgetRoom* btn = new WidgetRoom(
      i,
      GetRoomCoordX(i) - btn_size / 2,
      GetRoomCoordY(i) - btn_size / 2,
      btn_size,
      btn_size);
    this->add(btn);
    rooms_.push_back(btn);
  }
}

void WidgetMap::ClearRooms()
{
  for (auto& v : rooms_) {
    remove(v);
    delete v;
  }
  rooms_.clear();
  rooms_.resize(0);
}

void WidgetMap::ClearPlayer()
{ 
  // remove(player_);
}

void WidgetMap::ClearLines()
{
  // remove(pathes_);
  // delete pathes_;
}

void WidgetMap::SetCallbacks()
{
  for (auto& b : rooms_) {
    b->callback((Fl_Callback*)this->callback_, this->command_);
  }  
}

void WidgetMap::TuneAppearance()
{
  box(FL_PLASTIC_UP_FRAME);
}

}  // namespace wumpus_game
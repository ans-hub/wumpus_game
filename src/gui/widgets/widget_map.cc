// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: group widget represents map for main window

#include "widget_map.h"

namespace wumpus_game {

WidgetMap::WidgetMap ()
  : Fl_Group{30, 90, 600, 600}    // here was a bug when parent()->w()...h()
  , rooms_{}
  , pathes_{new WidgetNetdraw(1)}
  , player_{new WidgetPlayer()}
  // , level_{0}
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
  // level_ = level;
  begin();
  ResizeGroup(level);
  ClearRooms();
  DrawLines(level);
  DrawRooms(level);
  DrawPlayer();
  // SetRotateCallback();
  SetRoomsCallback();
  end();
}

// void WidgetMap::RedrawCurrentByRotate()
// {
  // auto angle = pathes_->GetCurrAngle() + 0.3;
  // pathes_->SetCurrAngle(angle);
  
  // ClearRooms();
  // DrawLines(level_);
  // DrawRooms(level_);      // how to mem marks on the room? state in simply words
  // SetRoomsCallback();
  
  // int offset_x = (player_->w()) / 2;
  // int offset_y = (player_->h()) / 2;
  // if (player_->IsReady()) {
  //   int room = player_->curr_room_;
  //   player_->position(GetRoomCoordX(room)-offset_x, GetRoomCoordY(room)-offset_y);
  // }
  // else {
  //   int room = player_->curr_room_;    
  //   // player_->position(, GetRoomCoordY(room)-offset_y);    
  //   player_->to_x_ = GetRoomCoordX(room)-offset_x;
  //   player_->to_y_ = GetRoomCoordY(room)-offset_y;
  // }

  // DrawPlayer();

  // parent()->redraw();
// }

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
  // move player every tick
  // player_->StaticMove(Point{});
}

void WidgetMap::DrawLines(int level)
{
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

// void WidgetMap::SetRotateCallback()
// {
  // level - take speed from settings
  // speed
  // double speed = 0.1;
  // Fl::add_timeout(speed, cb_rotate_map, this);
// }

void WidgetMap::SetRoomsCallback()
{
  for (auto& b : rooms_) {
    b->callback((Fl_Callback*)this->callback_, this->command_);
  }  
}

void WidgetMap::TuneAppearance()
{
  resizable(0); // not resize children
  box(FL_PLASTIC_UP_FRAME);
}

// void WidgetMap::cb_rotate_map(void* w)
// {
  // Fl::remove_timeout(cb_rotate_map, w);
  // ((WidgetMap*)w)->RedrawCurrentByRotate();
  // Fl::repeat_timeout(0.1, cb_rotate_map, w);
// }

}  // namespace wumpus_game
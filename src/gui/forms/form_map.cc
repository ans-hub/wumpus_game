// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: form represents map for main window

#include "form_map.h"

namespace wumpus_game {

FormMap::FormMap ()
  : Fl_Group(1, 1, 1, 1, "")
  , rooms_{}
  , pathes_{nullptr}
  , player_{nullptr}  // add separate as rooms and pathes
{
  form_helpers::tune_form(this);
} 

FormMap::~FormMap()
{
  for (auto& v : rooms_) {
    this->remove(v);
    delete v;
  }
  delete player_;
}

int FormMap::GetRoomCoordX(int num) const
{
  return pathes_->x() + pathes_->GetVertexes()[num].x_;
}

int FormMap::GetRoomCoordY(int num) const
{
  return pathes_->y() + pathes_->GetVertexes()[num].y_;
}

void FormMap::Redraw(int level)
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

void FormMap::ResizeGroup(int level)
{
  // evaluate based on edge len
  // and room btn too evaluated based on edge_len val
  // may be GetSizesForLevel???
  int w = draw_consts::level_width(level);
  this->resize(30, 90, w, w);
}

void FormMap::DrawPlayer()
{
  // remove(player_);
  player_ = new PlayerWidget();
  add(player_);
}

// Make form map in form _main. It is more simple to change sizes whe nlevel is new

void FormMap::DrawLines(int level)
{
  // int edge_len = draw_consts::edge_len;
  // remove(pathes_);
  pathes_ = new MapPathes(level);   // may be we set only x y w h and widget define by itself how to draw items???
  add(pathes_);
  pathes_->position(x(), y());   /// don`t forget to dothis
  // pathes_->redraw();
  // this->end(); 
}

void FormMap::DrawRooms(int level)
{
  int btn_size = draw_consts::room_btn_size;
  int rooms = draw_consts::level_vertexes(level);
  
  for (int i = 0; i < rooms; ++i) {
    RoomButton* btn = new RoomButton(
      i,
      GetRoomCoordX(i) - btn_size / 2,
      GetRoomCoordY(i) - btn_size / 2,
      btn_size,
      btn_size);
    this->add(btn);
    form_helpers::tune_button(btn);
    rooms_.push_back(btn);
  }
}

void FormMap::ClearRooms()
{
  for (auto& v : rooms_) {
    remove(v);
    delete v;
  }
  rooms_.clear();
  rooms_.resize(0);
}

void FormMap::ClearPlayer()
{ 
  remove(player_);
  delete player_;
}

void FormMap::ClearLines()
{
  remove(pathes_);
  delete pathes_;
}

void FormMap::SetCallbacks()
{
  for (auto& b : rooms_) {
    b->callback((Fl_Callback*)this->callback_, this->command_);
  }  
}

namespace form_helpers {

void tune_form(Fl_Group* w)
{
  w->box(FL_PLASTIC_UP_FRAME);
}

void tune_button(RoomButton*)
{
  // b->color((Fl_Color)36);
  // b->selection_color((Fl_Color)69);
  // b->labeltype(FL_SHADOW_LABEL);
  // b->labelcolor((Fl_Color)94);
}


}  // namespace form_helpers

}  // namespace wumpus_game
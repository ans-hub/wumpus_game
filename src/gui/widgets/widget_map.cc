// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: group widget represents map for main window

#include "widget_map.h"

namespace wumpus_game {

WidgetMap::WidgetMap ()
  : Fl_Group(1, 1, 1, 1, "")
  , rooms_{}
  , pathes_{nullptr}
  , player_{nullptr}  // add separate as rooms and pathes
{
  form_helpers::tune_form(this);
} 

WidgetMap::~WidgetMap()
{
  for (auto& v : rooms_) {
    this->remove(v);
    delete v;
  }
  delete player_;
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
  // evaluate based on edge len
  // and room btn too evaluated based on edge_len val
  // may be GetSizesForLevel???
  int w = draw_consts::level_width(level);
  this->resize(30, 90, w, w);
}

void WidgetMap::DrawPlayer()
{
  // remove(player_);
  player_ = new WidgetPlayer();   // Not raii!!
  add(player_);
}

// Make form map in form _main. It is more simple to change sizes whe nlevel is new

void WidgetMap::DrawLines(int level)
{
  // int edge_len = draw_consts::edge_len;
  // remove(pathes_);             // not raii!
  pathes_ = new WidgetNetdraw(level);   // may be we set only x y w h and widget define by itself how to draw items???
  add(pathes_);
  pathes_->position(x(), y());   /// don`t forget to dothis
  // pathes_->redraw();
  // this->end(); 
}

void WidgetMap::DrawRooms(int level)
{
  int btn_size = draw_consts::room_btn_size;
  int rooms = draw_consts::level_vertexes(level);
  
  for (int i = 0; i < rooms; ++i) {
    WidgetRoom* btn = new WidgetRoom(     //not raii
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
  remove(player_);
  delete player_;
}

void WidgetMap::ClearLines()
{
  remove(pathes_);
  delete pathes_;
}

void WidgetMap::SetCallbacks()
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

void tune_button(WidgetRoom*)
{
  // b->color((Fl_Color)36);
  // b->selection_color((Fl_Color)69);
  // b->labeltype(FL_SHADOW_LABEL);
  // b->labelcolor((Fl_Color)94);
}


}  // namespace form_helpers

}  // namespace wumpus_game
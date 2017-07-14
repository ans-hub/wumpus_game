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
{
  form_helpers::tune_form(this);
} 

FormMap::~FormMap()
{
  for (auto& v : rooms_) {
    this->remove(v);
    delete v;
  }
}

void FormMap::Redraw(int level)
{
  // clear map where???
  ResizeGroup(level);
  ClearRooms();
  DrawLines(level);
  DrawRooms(level);
  SetCallbacks();
}

// REALISATION DETAILS

void FormMap::DrawLines(int level)
{
  int edge_len = 10;
  pathes_ = new MapPathes(level, edge_len);
  this->add(pathes_);
  pathes_->position(120, 120);
  this->end();
}

void FormMap::DrawRooms(int level)
{
  int btn_size = 30;

  for (int i = 0; i < (level+3)*4; ++i) {
    RoomButton* btn = new RoomButton(
      i,
      pathes_->x() + pathes_->GetVertexes()[i].x_ - btn_size / 2,
      pathes_->y() + pathes_->GetVertexes()[i].y_ - btn_size / 2,
      btn_size,
      btn_size);
    this->add(btn);
    form_helpers::tune_button(btn);
    rooms_.push_back(btn);
  }
}


void FormMap::SetCallbacks()
{
  for (auto& b : rooms_) {
    b->callback((Fl_Callback*)this->callback_, this->command_);
  }  
}

void FormMap::ClearRooms()
{
  for (auto& v : rooms_) delete v;
  rooms_.clear();
  rooms_.resize(0);
}

void FormMap::ResizeGroup(int)
{
  // evaluate based on edge len
  // and room btn too evaluated based on edge_len val
  // may be GetSizesForLevel???
  this->resize(30, 80, 370, 335);
}

namespace form_helpers {

void tune_form(Fl_Group* w)
{
  w->box(FL_PLASTIC_UP_FRAME);
}

void tune_button(RoomButton* b)
{
  b->color((Fl_Color)36);
  b->selection_color((Fl_Color)69);
  b->labeltype(FL_SHADOW_LABEL);
  b->labelcolor((Fl_Color)94);
}

}  // namespace form_helpers

}  // namespace wumpus_game
// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: form represents map for main window

#include "form_map.h"

namespace wumpus_game {

FormMap::FormMap ()
  : Fl_Group(1, 1, 1, 1, "")
  , rooms_{}
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

void FormMap::DrawMap(int level)
{
  ResizeGroup(level);
  ClearRooms();
  DrawLines(level);
  DrawRooms(level);
  SetCallbacks();  
}

// REALISATION DETAILS

void FormMap::DrawRooms(int level)
{
  for (int i = 0; i < (level+3)*4; ++i) {

    RoomButton* btn = new RoomButton(i, (i*30)+20, 120, 30, 30);
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
  this->resize(30, 80, 370, 335);
}

// void FormMap::draw()
// {
//   // data member - level
//   struct Point{int x_; int y_; };
//   std::vector<Point> v;

//   int vx_total = 16;
//   int start_ivx = vx_total/2;
//   int ivx_total = vx_total/4;
//   int ovx_total = vx_total/4;
  
//   int fedge_len = 5;
//   int hedge_len = fedge_len/2;
  
//   int width = vx_total * fedge_len;
//   int height = width;

//   int center_pnt_x = width/2;
//   int center_pnt_y = height/2;

//   v.resize(vx_total);

//   // Fill inner 

//   int step = 2;
//   int radius = width / 2;
//   double angle_step = 360/ivx_total;
//   double angle = 0;
//   for (int i = start_ivx-1; i < vx_total; i += step) {
//     Point p;
//     p.x_ = cos(angle) * radius + center_pnt_x;
//     p.y_ = sin(angle) * radius + center_pnt_y;
//     v[i] = p;
//     angle += angle_step;
//   }

//   // Draw inner

//   // for (int i = start_ivx-1; i < ivx_total; i += step) {
//     fl_line (v[7].x_, v[8].y_, v[9].x_, v[9].y_);
//   // } 
// }

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
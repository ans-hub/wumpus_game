// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: group widget represents info and control table for game window

#include "widget_info.h"

namespace wumpus_game {

WidgetInfo::WidgetInfo (Images& images)
: Fl_Group(10, 70, 90, 90)
, images_{images}
, box_level_{new Fl_Box(x()+82, y()+20, 0, 0)}    // w and h is 0 since only
, box_wumps_{new Fl_Box(x()+8, y()+20, 0, 0)}     // this way i can arrange
, box_bats_{new Fl_Box(x()+8, y()+70, 0, 0)}
, box_pits_{new Fl_Box(x()+8, y()+45, 0, 0)}
, box_arrows_{new Fl_Box(x()+82, y()+45, 0, 0)}
, btn_continue_{new Fl_Button(x()+52, y()+60, 28, 20)}
, btn_next_{new Fl_Button(0,0,0,0)}
{
  TuneAppearance();
  end();
}

void WidgetInfo::Redraw(int level)
{
  int w = config::GetLevelWidth(level);
  int offset = config::main_wnd_offset; 

  this->image(
    images_.GetInfoImages(InfoStuff::COVER, level)
  );
  box_arrows_->image(
    images_.GetInfoImages(InfoStuff::ARROWS, level)
  );
  box_wumps_->image(
    images_.GetInfoImages(InfoStuff::WUMPS, level)
  );
  box_bats_->image(
    images_.GetInfoImages(InfoStuff::BATS, level)
  );
  box_pits_->image(
    images_.GetInfoImages(InfoStuff::PITS, level)
  );
  box_level_->image(
    images_.GetInfoImages(InfoStuff::LEVEL, level)
  );
  btn_continue_->image(
    images_.GetInfoImages(InfoStuff::CONTINUE_IMAGE, level)
  );
  btn_continue_->deimage(
    images_.GetInfoImages(InfoStuff::CONTINUE_DEIMAGE, level)
  );

  resize(offset + (w/2) - (90/2), (90/2)+(w/2), 90, 90);
  redraw();
}

void WidgetInfo::TuneAppearance()
{
  // btn_next_->hide();

  align(FL_ALIGN_INSIDE | FL_ALIGN_CENTER | FL_ALIGN_CLIP);
  labelcolor(FL_WHITE);

  helpers::TuneLhsIcons(box_wumps_);
  helpers::TuneLhsIcons(box_bats_);
  helpers::TuneLhsIcons(box_pits_);

  helpers::TuneRhsIcons(box_level_);
  helpers::TuneRhsIcons(box_arrows_);

  helpers::TuneRhsButtons(btn_continue_);
}

namespace helpers {
  
void TuneLhsIcons(Fl_Widget* w)
{
  w->align(Fl_Align(264));
  w->labelcolor(FL_WHITE);
  w->labelsize(10);
}

void TuneRhsIcons(Fl_Widget* w)
{
  w->align(Fl_Align(292));
  w->labelcolor(FL_WHITE);
  w->labelsize(10);
}

void TuneRhsButtons(Fl_Widget* w)
{
  w->align(Fl_Align(256));  
}

}  // namespace helpers

}  // namespace wumpus_game
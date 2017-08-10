// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: main window for gui windows container

#include "form_main.h"

namespace wumpus_game {

FormMain::FormMain(AudioOut& audio)
: Fl_Double_Window{0, 0, 0, 0, "Hunt the Wumpus"}
, img_cover_{nullptr}
, box_cover_{new Fl_Box(0, 0, 0, 0)}
, box_label_{new Fl_Box(0, 0, 0, 0, "HUNT THE WUMPUS")}
, wdg_info_{new WidgetInfo()}
, wdg_map_{new WidgetMap(audio)}
{
  TuneAppearance();
  end();
}

FormMain::~FormMain()
{
  delete img_cover_;
}

void FormMain::Redraw(int level)
{
  int offset = 30;
  int width = config::level_width(level) + offset * 2;
  int height = width + 60;
  
  int pos_x = (Fl::w() / 2) - (width / 2);
  int pos_y = (Fl::h() / 2) - (height / 2);
  resize(pos_x, pos_y, width, height);
  
  box_cover_->resize(0, 0, w(), h());
  box_label_->resize(30, 20, w()-60, 45);
  
  ClearBackgroundImage();
  SetBackgroundImage(level);
  
  wdg_map_->Redraw(level);
  wdg_info_->Redraw(level);
}

void FormMain::TuneAppearance()
{
  set_modal();
  color((Fl_Color)34);

  box_cover_->align(FL_ALIGN_INSIDE | FL_ALIGN_CENTER | FL_ALIGN_CLIP);
  box_label_->box(FL_PLASTIC_UP_FRAME);
  box_label_->color((Fl_Color)84);
  box_label_->labelsize(28);
  box_label_->labelcolor((Fl_Color)115);
}

void FormMain::SetBackgroundImage(int level)
{
  auto bg_name = config::GetBgImage(level);
  img_cover_ = new Fl_PNG_Image(bg_name.c_str());
  img_cover_ = helpers::resize_fl_image(img_cover_, box_cover_);
  box_cover_->image(img_cover_);
}

void FormMain::ClearBackgroundImage()
{
  delete img_cover_;
}

namespace helpers {

Fl_Image* resize_fl_image(Fl_Image* i, Fl_Widget* w)
{
  Fl_Image* old = i;
  Fl_Image* tmp = i->copy(w->w(), w->h());
  delete old;
  return tmp;
}

}  // namespace helpers

}  // namespace wumpus_game
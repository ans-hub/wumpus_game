// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: main window for gui windows container

#include "form_main.h"

namespace wumpus_game {

FormMain::FormMain(Images& images, AudioOut& audio)
: Fl_Double_Window{0, 0, 0, 0, "Hunt the Wumpus"}
, box_cover_{new Fl_Box(0, 0, 0, 0)}
, box_label_{new Fl_Box(0, 0, 0, 0, "HUNT THE WUMPUS")}
// , wdg_info_ {new WidgetInfo (images)}
, wdg_map_  {new WidgetMap  (audio, images)}
, images_{images}
{
  TuneAppearance();
  end();
}

void FormMain::Redraw(int level)
{
  int offset = 30;
  int width = config::GetLevelWidth(level) + offset * 2;
  int height = width + 60;
  int pos_x = (Fl::w() / 2) - (width / 2);
  int pos_y = (Fl::h() / 2) - (height / 2);
  
  this->resize(pos_x, pos_y, width, height);
  box_cover_->resize(0, 0, w(), h());
  box_label_->resize(30, 20, w()-60, 45);
  
  auto* bg = images_.GetMainBackground(
    level,
    box_cover_->w(),
    box_cover_->h()
  );
  box_cover_->image(bg);
  
  wdg_map_->Redraw(level);
  // wdg_info_->Redraw(level);
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

}  // namespace wumpus_game
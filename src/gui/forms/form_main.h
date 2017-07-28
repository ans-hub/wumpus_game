// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: main window for gui windows container

#ifndef FORM_MAIN_H
#define FORM_MAIN_H

#include <vector>
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Tiled_Image.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Window.H>

#include "../helpers/draw_consts.h"

namespace wumpus_game {

class FormMain : public Fl_Window 
{
public:
  FormMain();
  ~FormMain();
  void Show() { show(); }
  void Hide() { hide(); }
  void Redraw(int);
  
  Fl_PNG_Image*     img_cover_;
  Fl_Tiled_Image*   img_bg_;
  Fl_Box*           box_cover_;
  Fl_Box*           box_level_;
  Fl_Box*           box_label_;
  Fl_Button*        btn_continue_;
  Fl_Button*        btn_help_;

private:
  void TuneAppearance();
};

namespace gui_helpers {

  void cb_close_window(void*, void* w);

}

}  // namespace wumpus_game

#endif  //FORM_MAIN_H
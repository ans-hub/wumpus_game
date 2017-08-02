// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: main game window for `gui`

#ifndef FORM_MAIN_H
#define FORM_MAIN_H

#include <vector>
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Tiled_Image.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>

#include "gui/widgets/widget_info.h"
#include "gui/widgets/widget_map.h"
#include "gui/helpers/draw_consts.h"

namespace wumpus_game {

class Windows;

class FormMain : public Fl_Double_Window
{
public:
  FormMain();
  ~FormMain();
  void Show() { show(); }
  void Hide() { hide(); }
  void Redraw(int);
  
private:
  Fl_PNG_Image*     img_cover_;
  Fl_Tiled_Image*   img_bg_;
  Fl_Box*           box_cover_;
  Fl_Box*           box_level_;
  Fl_Box*           box_label_;
  WidgetMap*        wdg_map_;
  WidgetInfo*       wdg_info_;

  void TuneAppearance();
  friend Windows;
};

}  // namespace wumpus_game

#endif  //FORM_MAIN_H
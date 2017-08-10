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
#include <FL/Fl_Image.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>

#include "gui/widgets/widget_info.h"
#include "gui/widgets/widget_map.h"
#include "audio/audio_out.h"
#include "settings/config.h"

namespace wumpus_game {

class Windows;

class FormMain : public Fl_Double_Window
{
public:
  explicit FormMain(AudioOut&);
  virtual ~FormMain();
  
  void Redraw(int);
  
private:
  Fl_Image*         img_cover_;
  Fl_Box*           box_cover_;
  Fl_Box*           box_label_;
  WidgetInfo*       wdg_info_;
  WidgetMap*        wdg_map_;

  void TuneAppearance();
  void SetBackgroundImage(int);
  void ClearBackgroundImage();

  friend Windows;
};

namespace helpers {

  Fl_Image* resize_fl_image(Fl_Image*, Fl_Widget*);

}  // namespace helpers

}  // namespace wumpus_game

#endif  //FORM_MAIN_H
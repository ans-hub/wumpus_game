// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: main window for gui windows container

#ifndef FORM_MAIN_H
#define FORM_MAIN_H

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Window.H>

#include <vector>

#include "room_button.h"

namespace wumpus_game {

class FormMain : public Fl_Window 
{
public:
  typedef std::vector<RoomButton*> RoomButtons;
  
  FormMain();
  ~FormMain();

  RoomButtons       rooms_;
  Fl_Window*        window_;
  Fl_PNG_Image*     img_level_;
  Fl_PNG_Image*     img_cover_;
  Fl_Box*           box_cover_;
  Fl_Box*           box_level_;
  Fl_Box*           box_label_;
  Fl_Button*        btn_start_;
  Fl_Button*        btn_help_;
  Fl_Button*        btn_quit_;
  Fl_Text_Buffer*   output_;
  Fl_Text_Display*  display_;
private:
  void TuneAppearance();
};

}  // namespace wumpus_game

#endif  //FORM_MAIN_H
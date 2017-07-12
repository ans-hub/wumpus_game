// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: windows container for `gui` view and cotroller

#ifndef GUI_WINDOWS_H
#define GUI_WINDOWS_H

#include "forms/form_main.h"
#include "forms/form_popup.h"

namespace wumpus_game {

struct Windows
{
  Windows();
  ~Windows();
  
  FormMain*   main_wnd_;
  FormPopup*  popup_wnd_;
};

}  // namespace wumpus_game

#endif  // GUI_WINDOWS_H
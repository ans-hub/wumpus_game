// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: windows container for `gui` view and cotroller

#ifndef GUI_WINDOWS_H
#define GUI_WINDOWS_H

#include "FL/fl_ask.H"

#include "forms/form_start.h"
#include "forms/form_help.h"
#include "forms/form_main.h"
#include "forms/form_info.h"
#include "forms/form_map.h"

namespace wumpus_game {

class Windows
{
public:
  Windows();
  ~Windows();
  void Show();
  void Close();
  void Redraw(int);
  void ShowMain() const;
  void HideMain() const;
  void ShowHelp() const;
  void HideHelp() const;
  void ShowWidget(Fl_Widget*);
  void HideWidget(Fl_Widget*);
  
  FormStart*    wnd_start_;
  FormHelp*     wnd_help_;
  FormMain*     wnd_main_;
  FormMap*      wdg_map_;
  FormInfo*     wdg_info_;

private:
  void SetChildrenCallbacks();    // see note #1

};

namespace gui_helpers {

  void cb_help_button(void*, void*);
  void cb_quit_help_button(void*, void*);
  void cb_close_wnd_main_(void*, void*);

}  // namespace gui_helpers

}  // namespace wumpus_game

#endif  // GUI_WINDOWS_H

// Note #1 : main gui sets callbacks that not depends on game logic,
// but only based on form showing and opening logic
// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: model's `view` using gui

#ifndef GUI_VIEW_H
#define GUI_VIEW_H

#include <string>
#include <queue>

#include "3rdparty/observer.h"
#include "gui/windows.h"
#include "entities/logic.h"
#include "gui/helpers/trajectory.h"
#include "entities/helpers.h"
#include "enums/enums.h"
#include "config.h"

namespace wumpus_game {

class GuiView : public mvc_set::Observer<Event>
{
public:
  using RoomEvent = std::pair<Event, int>;
  using Events = std::queue<RoomEvent>;

  GuiView(const Logic&, Windows&);
  ~GuiView() { }

private:
  const Logic&    model_;
  Windows&        gui_;
  Events          events_;
  
  bool IncomingNotify(Event) override;    // register event
  void ProcessNextEvent();                // get event from queue
  void ExecuteEvent(Event, int);          // execute concrete event

  static void cb_process_next_event(void*);

};

namespace gui_helpers {

  void play_bg_music(Windows&, const Logic&);
  void refresh_info_widget(Windows&, const Logic&);
  void enable_buttons(Windows&);
  void disable_buttons(Windows&);
  void show_level(Windows&, const Logic&);
  void hide_level(Windows&, const Logic&);
  void show_error_room(Windows&);
  void show_player_position_instantly(Windows&, const Logic&);
  void show_player_movement(Windows&, int);
  void show_bats_movement(Windows&, int);
  void show_player_shot(Windows&);
  void show_havent_arrows(Windows&);
  void show_feels(Windows&, const Logic&, int);
  void show_game_over(Windows&, const Logic&);
  void show_killed_one_wump(Windows&);
  void mark_room_as_wisited(Windows&, const Logic&, int);

}  // namespace gui_helpers

}  // namespace wumpus_game

#endif // GUI_VIEW_H
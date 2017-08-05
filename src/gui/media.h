// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: model's `view` using gui

#ifndef MEDIA_H
#define MEDIA_H

#include <string>
#include <deque>

#include "3rdparty/observer.h"
#include "gui/windows.h"
#include "entities/events.h"
#include "entities/logic.h"
#include "helpers/trajectory.h"
#include "settings/config.h"
#include "audio/audio_out.h"

namespace wumpus_game {

struct Media : public mvc_set::Observer<Event>
{
  using RoomEvent = std::pair<Event, int>;
  using Events = std::deque<RoomEvent>;

  Media(const Config&, const Logic&, Windows&, const AudioOut&);
  ~Media() { }

private:
  const Config&   conf_;
  const Logic&    model_;
  Windows&        gui_;
  const AudioOut& audio_;
  Events          events_;
  bool            ready_;

  bool IncomingNotify(Event) override;    // register event
  void ProcessNextEvent();                // get event from queue
  void ExecuteEvent(Event, int);          // execute concrete event
  void DoNotDistrubeWhileAnimate() { ready_ = false; }
  void CheckReadyToNextEvent();
  void ReturnEventBack(Event, int);

  static void cb_process_next_event(void*);
  static void cb_check_ready_to_next_event(void*);

};

namespace gui_helpers {

  void refresh_info_widget(Windows&, const Logic&);
  void enable_buttons(Windows&);
  void disable_buttons(Windows&);
  void show_level(Windows&, const Logic&);
  void hide_level(Windows&);
  void show_error_room(Windows&);
  void show_player_position_instantly(Windows&, const Logic&);
  bool show_player_movement(Windows&, int);
  bool show_bats_movement(Windows&, int);
  void show_player_shot(Windows&);
  void show_havent_arrows(Windows&);
  void show_feels(Windows&, const Logic&, int);
  void show_game_over(Windows&, const Logic&);
  void show_killed_one_wump(Windows&);
  Point get_offsetted_point_of_room(Windows&, int);
  
}  // namespace gui_helpers

}  // namespace wumpus_game

#endif //MEDIA_H
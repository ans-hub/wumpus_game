// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: performs music playing in game (not events sounds)

#ifndef MUSIC_H
#define MUSIC_H

#include <queue>
#include <string>

#include <FL/Fl.H>

#include "3rdparty/observer.h"
#include "3rdparty/audio_out.h"

#include "entities/logic.h"
#include "enums/enums.h"
#include "config.h"

namespace wumpus_game {

class Music : public mvc_set::Observer<Event>
{
public:
  using Events = std::queue<Event>;

  Music(const Logic&, AudioOut&);
  ~Music() { }

private:
  const Logic&  model_;
  AudioOut&     audio_;
  Events        events_;
  
  bool IncomingNotify(Event) override;    // register event
  void ProcessNextEvent();                // get event from queue
  void ExecuteEvent(Event);          // execute concrete event

  static void cb_process_next_event(void*);
};

namespace helpers {

  void PlayBackgroundMusic(AudioOut&, const Logic&);
  void PreloadBackgroundMusic(AudioOut&);

}  // namespace helpers

}  // namespace wumpus_game

#endif // MUSIC_H
// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: performs background music playing in game (not events sounds)

#ifndef MUSIC_H
#define MUSIC_H

#include <queue>
#include <string>

#include <FL/Fl.H>

#include "3rdparty/observer.h"
#include "3rdparty/audio/audio_out.h"

#include "entities/logic.h"
#include "enums/enums.h"
#include "config.h"

namespace wumpus_game {

class Music : public mvc_set::Observer<Event>
{
public:
  using Events = std::queue<Event>;
  using AudioOut = anshub::AudioOut;

  Music(const Logic&, AudioOut&);
  ~Music() { }

private:
  const Logic&  model_;
  AudioOut&     audio_;
  Events        events_;
  
  bool IncomingNotify(Event) override;
  void ProcessNextEvent();
  void ExecuteEvent(Event);

  static void cb_process_next_event(void*);
};

namespace music_helpers {
  using AudioOut = anshub::AudioOut;

  void PlayMainMusic(AudioOut&);
  void PlayBackgroundMusic(AudioOut&, const Logic&);
  void PreloadBackgroundMusic(AudioOut&);

}  // namespace music_helpers

}  // namespace wumpus_game

#endif // MUSIC_H
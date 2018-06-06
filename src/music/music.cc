// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: performs background music playing in game (not events sounds)

#include "music.h"

namespace wumpus_game {

Music::Music(const Logic& model, AudioOut& audio)
  : model_{model}
  , audio_{audio}
  , events_{}
{
  music_helpers::PreloadBackgroundMusic(audio_);
  music_helpers::PlayMainMusic(audio_);
  
  Fl::add_timeout(0.02, cb_process_next_event, this);
}

bool Music::IncomingNotify(Event msg)
{
  events_.push(msg);
  return true;
}

void Music::ProcessNextEvent()
{
  if (!events_.empty()) {
    Event msg = events_.front();
    ExecuteEvent(msg);
    events_.pop();
  }
}

void Music::ExecuteEvent(Event msg)
{
  if (msg ==  Event::NEW_LEVEL)
    music_helpers::PlayBackgroundMusic(audio_, model_);
}

void Music::cb_process_next_event(void* m)
{
  ((Music*)m)->ProcessNextEvent();
  Fl::repeat_timeout(0.02, cb_process_next_event, m);
}

// CLASS HELPERS

void music_helpers::PlayMainMusic(AudioOut& audio)
{
  auto main_music = config::GetBackgroundMusic(1);  
  audio.Play(main_music);
}

void music_helpers::PlayBackgroundMusic(AudioOut& audio, const Logic& model)
{
  auto level = model.CurrentLevel();
  auto level_music = config::GetBackgroundMusic(level);
  bool is_playing = anshub::audio_helpers::IsNowPlaying(audio, level_music);
  
  if (!is_playing) {
    anshub::audio_helpers::StopAllNowPlaying(audio, false);
    audio.Play(level_music);
  }
}

void music_helpers::PreloadBackgroundMusic(AudioOut& audio)
{
  for (int i = 1; i <= config::levels_max; ++i)
    audio.Load(config::GetBackgroundMusic(i), true);
}

}  // namespace wumpus_game
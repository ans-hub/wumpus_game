// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: class that represents audio output in game

#include "audio_output.h"

namespace wumpus_game {

AudioOutput::AudioOutput(const Config& conf)
  : inited_{false}
  , handles_{ }
  , conf_{conf}
{
  if (BASS_Init(-1, 44100, BASS_DEVICE_DEFAULT, 0, 0)) {
    inited_ = true;
    Play("../src/audio/wav/cave_theme.wav", true);
  }
}

AudioOutput::~AudioOutput()
{
  for (auto& h : handles_) BASS_SampleFree(h);
  if (!inited_) BASS_Free();
}

void AudioOutput::Play(const char* file, bool repeat)
{
  HSAMPLE handle = BASS_SampleLoad(FALSE, file, 0,0,3, repeat ? 4 : 1 );
  handle = BASS_SampleGetChannel(handle, FALSE);
  handles_.push_back(handle);

  BASS_ChannelSetAttribute(handle, BASS_ATTRIB_VOL,0.5f);
  BASS_ChannelPlay(handle, FALSE);
}

// remake to queue model
// bool AudioOutput::IncomingNotify(Event msg)
// {
  // if (!Inited()) return false;
  // switch(msg)
  // {
  //   case Event::PLAYER_DOES_MOVE :
  //     Play("../src/audio/wav/player_move.wav", false);
  //     break;
  //   case Event::PLAYER_DOES_SHOT :
  //     Play("../src/audio/wav/player_shot.wav", false);
  //     break;
  //   case Event::ONE_WUMP_KILLED :
  //     Play("../src/audio/wav/wump_killed.wav", false);
  //     break;
  //   case Event::MOVED_BATS :
  //     Play("../src/audio/wav/moved_bats.wav", false);
  //     break;
  //   case Event::GAME_OVER :
  //     switch (logic_.GameOverCause()) {
  //       case Logic::SubjectID::PLAYER :

  //         break;
  //       case Logic::SubjectID::WUMP :

  //         break;
  //       case Logic::SubjectID::PIT :
  //         Play("../src/audio/wav/player_pits.wav", false);
  //         break;
  //       case Logic::SubjectID::UNKNOWN : default : break;
  //     }
  //   default : break;
  // }
  // return true;
// }

}  // namespace wumpus_game
// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: class that represents sounds in game

#include "game_sounds.h"

namespace wumpus_game {

GameSounds::GameSounds()
  : inited_ {false}
  , handles_{ }
{
  if (BASS_Init(-1, 44100, BASS_DEVICE_DEFAULT, 0, 0))
    inited_ = true;
}

GameSounds::~GameSounds()
{
  for (auto& h : handles_) BASS_SampleFree(h);
  if (!inited_) BASS_Free();
}

void GameSounds::Play(const char* file, bool repeat)
{
  HSAMPLE handle = BASS_SampleLoad(FALSE, file, 0,0,3, repeat ? 4 : 1 );
  handle = BASS_SampleGetChannel(handle, FALSE);
  handles_.push_back(handle);

  BASS_ChannelSetAttribute(handle,BASS_ATTRIB_VOL,0.5f);
  // BASS_ChannelSetAttribute(handle,BASS_ATTRIB_PAN,((rand()%201)-100)/100.f);
  BASS_ChannelPlay(handle, FALSE);
}
// remake to queue model
bool GameSounds::IncomingNotify(Event msg)
{
  if (!Inited()) return false;
  switch(msg)
  {
    case Event::NEW_LEVEL :
      // Play("../src/audio/wav/cave_theme.wav", true);
      break;
    case Event::PLAYER_DOES_MOVE :
      Play("../src/audio/wav/player_walk.wav", false);
      break;
    case Event::PLAYER_DOES_SHOT :
      Play("../src/audio/wav/player_shot.wav", false);
      break;
    case Event::ONE_WUMP_KILLED :
      Play("../src/audio/wav/wump_killed.wav", false);
      break;
    default : break;
  }
  return true;
}

}  // namespace wumpus_game
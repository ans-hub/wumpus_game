// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: class that represents audio output in game

#include "audio_out.h"

namespace wumpus_game {

AudioOut::AudioOut(const Config& conf)
  : inited_{false}
  , loaded_{ }
  , conf_{conf}
{
  if (BASS_Init(-1, 44100, BASS_DEVICE_DEFAULT, 0, 0))
    inited_ = true;
}

AudioOut::~AudioOut()
{
  for (auto& a : loaded_) BASS_SampleFree(a.second);
  if (!inited_) BASS_Free();
}

AudioOut::Handle AudioOut::Load(const std::string& fname, bool repeat)
{
  Handle hndl = Find(fname);
  if (!hndl) {
    hndl = BASS_SampleLoad(FALSE, fname.c_str(), 0,0,3, repeat ? 4 : 1 );
    loaded_.push_back(std::make_pair(fname, hndl));
  }
  return hndl;
}

AudioOut::Handle AudioOut::Find(const std::string& fname) const
{
  for (auto& l:loaded_) {
    if (l.first == fname) return l.second;
  }
  return 0;
}

bool AudioOut::Play(const std::string& fname, bool repeat)
{
  Handle hndl = Load(fname, repeat);
  if (!hndl) return false;

  hndl = BASS_SampleGetChannel(hndl, FALSE);
  BASS_ChannelSetAttribute(hndl, BASS_ATTRIB_VOL,0.5f);

  if (BASS_ChannelPlay(hndl, FALSE)) 
    return true;
  return false;
}

bool AudioOut::Stop(const std::string& fname)
{
  Handle hndl = Find(fname);
  if (hndl) 
    return BASS_SampleStop(hndl);
  return false;
}

}  // namespace wumpus_game
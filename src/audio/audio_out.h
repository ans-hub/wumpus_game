// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: class that represents audio output in game

#ifndef AUDIO_OUT_H
#define AUDIO_OUT_H

#include <vector>
#include <string>
#include <memory>

#include "3rdparty/bass.h"
#include "settings/config.h"

namespace wumpus_game {

struct AudioOut
{
  using Handle = HSAMPLE;
  using FileName = std::string;
  using VHandles = std::vector<Handle>;
  using VSounds = std::vector<std::pair<FileName, Handle>>;

  AudioOut();
  ~AudioOut();

  bool      Play(const FileName&, bool = false);
  bool      Stop(const FileName&);
  Handle    Load(const FileName&, bool);
  FileName  NowPlayingRepeated() const;
private:
  bool        inited_;
  VSounds     loaded_;
  
  Handle    Find(const FileName&) const;
  bool      IsRepeatedSample(const Handle&) const;
  VHandles  GetLoadedChannels(const Handle&) const;
  bool      IsChannelsPlayingNow(const VHandles&) const;
  
};

}  // namespace wumpus_game

#endif  // AUDIO_OUT_H
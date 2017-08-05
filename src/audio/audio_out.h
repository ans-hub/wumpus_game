// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: class that represents audio output in game

#ifndef AUDIO_OUT_H
#define AUDIO_OUT_H

#include <vector>
#include <string>

#include "3rdparty/bass.h"
#include "settings/config.h"

namespace wumpus_game {

struct AudioOut
{
  using Handle = HSAMPLE;
  using Sounds = std::vector<std::pair<std::string, Handle>>;

  explicit AudioOut(const Config&);
  ~AudioOut();

  bool Play(const std::string&, bool = false);
  bool Stop(const std::string&);  // bool - stop immediately
private:
  bool          inited_;
  Sounds        loaded_;
  const Config& conf_;

  Handle  Load(const std::string&, bool);
  Handle  Find(const std::string&) const;
};

}  // namespace wumpus_game

#endif  // AUDIO_OUT_H
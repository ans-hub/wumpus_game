// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: class that represents audio output in game

#ifndef AUDIO_OUTPUT_H
#define AUDIO_OUTPUT_H

#include <vector>

#include "3rdparty/bass.h"
#include "settings/config.h"

namespace wumpus_game {

struct AudioOutput
{
  using Handles = std::vector<HSAMPLE>;

  explicit AudioOutput(const Config&);
  ~AudioOutput();
  bool Inited() const { return inited_; }
  void Play(const char*, bool);
private:
  bool          inited_;
  Handles       handles_;
  const Config& conf_;
};

}  // namespace wumpus_game

#endif  // AUDIO_H
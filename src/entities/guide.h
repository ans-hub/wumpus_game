// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: interface to class Guide represents guide in the cave

#ifndef GUIDE_H
#define GUIDE_H

#include "entities/subject.h"
#include "entities/helpers.h"

namespace wumpus_game {

class Guide : public Subject
{
public:
  explicit Guide(Map*);
  ~Guide() { }
  Guide(Guide&& old);
  Guide& operator=(Guide&&);
};

}  // namespace wumpus_game

#endif  // GUIDE_H
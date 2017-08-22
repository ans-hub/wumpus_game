// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: implementation of class Guide represents guide in the cave

#include "guide.h"

namespace wumpus_game {

Guide::Guide(Map* cave)
  : Subject(cave)
{
  type_ = Subject::GUIDE;
}

Guide::Guide(Guide&& old)
  : Subject(std::move(old))
{ }

Guide& Guide::operator=(Guide&& old)
{
  Subject::operator=(std::move(old));
  return *this;
}

}  // namespace wumpus_game
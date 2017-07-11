// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: implementation of the logic helpers

#include "logic_helpers.h"

namespace wumpus_game {

namespace helpers {

void worry_neighboring_wumps(VWumpsPtr& wumps, std::vector<int>& neighbors)
{
  for (auto& w : wumps) {
    int room = w->GetCurrRoomNum(); 
    if (find_in_vector(neighbors, room)) w->Worried(true);
  }
}

bool kill_one_wump_in_room(VWumpsPtr& wumps, int room)
{
  for (auto& w : wumps) {
    if (w->GetCurrRoomNum() == room) {
      w->Kill();
      return true;
    }
  }
  return false;
}

bool is_in_one_room(Subject* subj1, Subject* subj2)
{
  if (subj1->GetCurrRoomNum() == subj2->GetCurrRoomNum())
    return true;
  return false;
}

}  // namespace helpers

}  // namespace wumpus_game
// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: implementation of the helpers

#include "helpers.h"

namespace wumpus_game {

// LABYRINTH HELPERS

namespace helpers {

// Returns neighbor room numbers 

std::vector<int> get_neighboring_rooms(int room_num, const Labyrinth& cave)
{
  Room* room = cave.GetRoom(room_num);
  return { room->left_->num_
         , room->right_->num_
         , room->back_->num_
  };
}

// Returns bool if room num_1 and room num_2 is neighbors

bool is_neighboring_rooms(int num_1, int num_2, const Labyrinth& cave)
{
  if (num_1 == num_2) return false;

  auto neighbors = get_neighboring_rooms(num_1, cave);
  auto result = std::find(std::begin(neighbors), std::end(neighbors), num_2);

  if (result != std::end(neighbors)) {
    return true;
  }
  return false;
}

}  // namespace helpers

}  // namespace wumpus_game
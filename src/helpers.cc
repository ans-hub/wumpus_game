// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: implementation of the helpers

#include "helpers.h"

namespace wumpus_game {

// MAP HELPERS

namespace helpers {

// Returns neighbor room numbers 

std::vector<int> get_neighboring_rooms(int room_num, const Map& cave)
{
  Room* room = cave.GetRoom(room_num);
  return { room->left_->num_
         , room->right_->num_
         , room->back_->num_
  };
}

// Returns bool if room num_1 and room num_2 is neighbors

bool is_neighboring_rooms(int num_1, int num_2, const Map& cave)
{
  if (num_1 == num_2) return false;

  auto neighbors = get_neighboring_rooms(num_1, cave);
  auto result = std::find(std::begin(neighbors), std::end(neighbors), num_2);

  if (result != std::end(neighbors)) {
    return true;
  }
  return false;
}

// Represents std::vector<int> in std::string

std::string vint_to_string(const std::vector<int> &v, std::string delim)
{
  std::stringstream sst;
  for (std::size_t i = 0; i < v.size(); ++i) {
    if (i != 0) sst << delim;
    sst << v.at(i);
  }
  return sst.str();
}


}  // namespace helpers

}  // namespace wumpus_game
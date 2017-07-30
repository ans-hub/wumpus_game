// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: constants and rules for window drawings

#include "draw_consts.h"

namespace wumpus_game {

namespace draw_consts {
  
int level_vertexes(int level)
{ 
  return (level+4)*4;
}

double level_width(int level)
{
  // remove magic const
  // if (level == 1 || level == 2 || level == 3) level = 2; // prevent too small window
  // return level_vertexes(level) * edge_len * 2;
  return level_vertexes(2) * edge_len * 2;
} 

}  // namespace draw_consts

}  // namespace wumpus_game
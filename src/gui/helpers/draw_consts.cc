// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: constants and rules for window drawings

#include "draw_consts.h"

namespace wumpus_game {

namespace draw_consts {
  
int level_vertexes(int level)
{ 
  return (level+3)*4;
}

double level_width(int level)
{
  return level_vertexes(level) * edge_len * 2;
} 

}  // namespace draw_consts

}  // namespace wumpus_game
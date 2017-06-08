// pit.cc: Anton Novoselov @ 2017
// Excercise #12 from Stroustrup`s book
// Topic: vectors and arrays (game "Hunt the Wumpus")
// Description: the bottomless pit class

#include "pit.h"

namespace anshub {

std::string Pit::FeelsRepresent() const
{
  return "FEELS: You feel the cold (possible the bottomless pit is near)";
}

}
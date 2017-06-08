// enemy.cc: Anton Novoselov @ 2017
// Excercise #12 from Stroustrup`s book
// Topic: vectors and arrays (game "Hunt the Wumpus")
// Description: enemy abstract class

#include "bat.h"

namespace anshub {

std::string Bat::FeelsRepresent() const
{
  return "FEELS: You feel the wind (possible the bats is near)";
}

}
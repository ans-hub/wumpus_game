// wump.cc: Anton Novoselov @ 2017
// Excercise #12 from Stroustrup`s book
// Topic: vectors and arrays (game "Hunt the Wumpus")
// Description: wump class

#include "wump.h"

namespace anshub {

std::string Wump::FeelsRepresent() const
{
  return "FEELS: It`s smeels like Wumpus (possible the Wumpus is near)";
}

}
// room.cc: Anton Novoselov @ 2017
// Excercise #12 from Stroustrup`s book
// Topic: vectors and arrays (game "Hunt the Wumpus")
// Description: room of labyrinth implementation

#include "room.h"

namespace anshub {

bool Room::IsEmpty() const
{
  return (persons_.empty()) ? true : false;
}
}
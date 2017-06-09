// subject.cc: Anton Novoselov @ 2017
// Excercise #12 from Stroustrup`s book
// Topic: vectors and arrays (game "Hunt the Wumpus")
// Description: subject abstract class
//
// Note 1 : first init in zero room, needs to CheckIn procedure
// Note 2 : since tunnels count is 3, we choose from 1 to 3

#include "subject.h"

namespace anshub {

Subject::Subject(const Labyrinth& cave)
: dead_{false}
, type_{UNKNOWN}
, cave_{cave}
, curr_room_{nullptr}
{
  curr_room_ = cave.GetRoom(0);    // see note #1
  CheckIn();
  TeleportRandom();
}

bool Subject::Move(int room, std::string& msg)
{
  if (room >= cave_.GetSize()) {
    msg = "Wrong room number";
    return false;
  }
  else if (cave_.IsNeighbors(room, curr_room_->num_)) {
    return Teleport(room, msg);
  }
  else {
    msg = "Not neighbor room";
    return false;
  }
}

bool Subject::Teleport(int room, std::string& msg)
{
  if (room >= cave_.GetSize()) {
    msg = "Wrong room number";
    return false;
  }
  else if (room == curr_room_->num_) {
    msg = "Already here";
    return false;
  }
  else {
    msg = "Succesfull";
    CheckOut();
    curr_room_ = cave_.GetRoom(room);
    CheckIn();
    return true;
  } 
}

bool Subject::MoveRandom()
{
  std::string msg{""};
  int room {GetRandomInt(1,3)};   // see note #2
  switch(room)
  {
    case 1  : return Move(curr_room_->left_->num_, msg);
    case 2  : return Move(curr_room_->right_->num_, msg);
    case 3  : return Move(curr_room_->back_->num_, msg);
  }
  return false;
}


bool Subject::TeleportRandom()
{
  do {
    int rand_room = GetRandomInt(0, cave_.GetSize()-1);
    if (cave_.GetRoom(rand_room)->IsEmpty()) {
      std::string msg{};
      return Teleport(rand_room, msg);
    }
  } while(true);
}

Subject::Persons Subject::ExamineRoom() const
{
  Persons persons;
  for (auto const p : curr_room_->persons_) {
    if (p != this) persons.push_back(p->GetType());
  }
  return persons;
}

void Subject::CheckIn()
{
  curr_room_->persons_.push_back(this);
}

void Subject::CheckOut()
{
  std::vector<const Subject*>& p = curr_room_->persons_;
  p.erase (
    std::remove (p.begin(), p.end(), this), p.end()
  );
}

int GetRandomInt(int i, int k)
{
  return std::experimental::randint(i, k);
}

}
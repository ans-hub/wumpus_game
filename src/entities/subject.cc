// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: implementation of the Subject class

#include "subject.h"

namespace wumpus_game {

Subject::Subject(Map& cave)
  : dead_{false}
  , type_{Person::UNKNOWN}
  , curr_room_{nullptr}
  , cave_{cave}
{
  rand_toolkit::start_rand();
  curr_room_ = cave.GetRoom(0);
  CheckIn();
  TeleportRandom();
}

Subject::Subject(Subject&& old)
  : dead_{old.dead_}
  , type_{old.type_}
  , curr_room_{old.curr_room_}
  , cave_{old.cave_} { }

Subject& Subject::operator=(Subject&& old)
{
  this->dead_ = old.dead_;
  this->type_ = old.type_;
  this->curr_room_ = old.curr_room_;
  return *this;
}

bool Subject::Move(int to_room, std::string& msg)
{
  int from_room = curr_room_->num_;

  if (to_room >= cave_.GetSize()) {
    msg = "Wrong room number";
    return false;
  }
  else if (helpers::is_neighboring_rooms(to_room, from_room, cave_)) {
    return Teleport(to_room, msg);
  }
  else {
    msg = "Not neighbor room";
    return false;
  }
}

bool Subject::Teleport(int to_room, std::string& msg)
{
  int from_room = curr_room_->num_;

  if (to_room >= cave_.GetSize()) {
    msg = "Wrong room number";
    return false;
  }
  else if (to_room == from_room) {
    msg = "Already here";
    return false;
  }
  else {
    msg = "Succesfull";
    CheckOut();
    curr_room_ = cave_.GetRoom(to_room);
    CheckIn();
    return true;
  } 
}

bool Subject::MoveRandom()
{
  std::string msg{""};
  int room {rand_toolkit::get_rand(1,3)};  // since tunnels count is eq 3
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
    int rand_room = rand_toolkit::get_rand(0, cave_.GetSize()-1);
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
  std::vector<Subject*>& p = curr_room_->persons_;
  p.erase (
    std::remove (p.begin(), p.end(), this), p.end()
  );
}

}  // namespace wumpus_game
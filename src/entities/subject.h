// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: interface to the Subject abstract class

#ifndef SUBJECT_H
#define SUBJECT_H

#include <string>
#include "../3rdparty/rand_toolkit.h"

#include "map.h"
#include "../helpers.h"

namespace wumpus_game {

struct Room;

class Subject
{
public:
  enum Person { // remake in Type
    UNKNOWN = 0,
    EMPTY,
    PLAYER,
    ENEMY,
    WUMP,
    PIT,
    BAT
  };

  typedef std::vector<Person> Persons;

  explicit Subject(Map&);
  virtual ~Subject() { CheckOut(); }
  Subject(const Subject&) =delete;
  Subject& operator=(const Subject&) =delete;
  Subject(Subject&&);
  Subject& operator=(Subject&&);

  bool    Move(int, std::string&);     // see note #1 after code
  bool    Teleport(int, std::string&);
  bool    MoveRandom();
  bool    TeleportRandom();
  Persons ExamineRoom() const;

  Person  GetType() const { return type_; }
  int     GetCurrRoomNum() const { return curr_room_->num_; }
  void    Kill() { dead_ = true; }
  void    Alive() { dead_ = false; }

protected:
  void    CheckIn();    // see note #2 after code
  void    CheckOut();

  bool    dead_;
  Person  type_;        // see note #3 after code
  Room*   curr_room_;
  Map&    cave_;
};

}  // namespace wumpus_game

#endif  // SUBJECT_H

// Interface notes:
//
// #1 : msg contains the reason why Move() and Teleport() returns true
// or false values
//
// #2 : performing check-in and check-out of subject in the room its
// stayed by placing/removing its pointer to the container of current room instance
//
// #3 : needs to define a subject type, setted in ctors of derived classes 
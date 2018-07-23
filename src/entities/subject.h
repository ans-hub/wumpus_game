// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: interface to the Subject abstract class

#ifndef SUBJECT_H
#define SUBJECT_H

#include <string>
#include "3rdparty/rand_toolkit.h"
#include "entities/map.h"

namespace wumpus_game {

struct Room;

class Subject
{
public:
  enum ID {
    UNKNOWN = 0,
    EMPTY,
    PLAYER,
    ENEMY,
    WUMP,
    PIT,
    BAT,
    GUIDE
  };

  typedef std::vector<ID> VSubjectsId;
  typedef std::vector<Subject*> VSubjects;

  explicit Subject(Map*);
  virtual ~Subject() { CheckOut(); }
  Subject(const Subject&) =delete;
  Subject& operator=(const Subject&) =delete;
  Subject(Subject&&);
  Subject& operator=(Subject&&);

  bool    Move(int, std::string&);
  bool    Teleport(int, std::string&);
  bool    MoveRandom();
  bool    TeleportRandom();

  ID      GetType() const { return type_; }
  int     GetCurrRoomNum() const { return curr_room_->num_; }
  void    Kill() { dead_ = true; }
  void    Alive() { dead_ = false; }
  bool    IsLive() { return !dead_; }

protected:
  void    CheckIn();
  void    CheckOut();

  bool    dead_;
  ID      type_;
  Room*   curr_room_;
  Map*    cave_;
};

}  // namespace wumpus_game

#endif  // SUBJECT_H

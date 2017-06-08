// subject.h: Anton Novoselov @ 2017
// Excercise #12 from Stroustrup`s book
// Topic: vectors and arrays (game "Hunt the Wumpus")
// Description: subject abstract class
//
// Note # 1 : msg contains the reason why Move() and Teleport() returns true
// or false values
//
// Note # 2 : performing check-in and check-out of subject in the room its
// stay by placing/removing its pointer to the container of current room instance
//
// Note # 3 : needs to define a subject type, setted in ctors of derived classes 

#include <string>
#include <experimental/random>

#ifndef SUBJECT_H
#define SUBJECT_H

#include "labyrinth.h"

namespace anshub {

struct Room;

class Subject
{
public:
  enum Person {
    UNKNOWN = 0,
    EMPTY,
    PLAYER,
    ENEMY,
    WUMP,
    PIT,
    BAT
  };
  
  typedef std::vector<Person> Persons;

  explicit Subject(const Labyrinth&);
  virtual ~Subject() { CheckOut(); }
  Subject(const Subject&) =delete;

  bool    Move(int room, std::string& msg);     // see note #1
  bool    Teleport(int room, std::string& msg);
  bool    MoveRandom();
  bool    TeleportRandom();
  Persons ExamineRoom() const;

  Person  GetType() const { return type_; }
  int     GetCurrRoomNum() const { return curr_room_->num_; }
  void    Kill() { dead_ = true; }

protected:
  void    CheckIn();    // see note #2
  void    CheckOut();

  bool        dead_;
  Person      type_;    // see note #3
  const Labyrinth&  cave_;
  Room*       curr_room_;
};

int GetRandomInt(int, int);

}

#endif
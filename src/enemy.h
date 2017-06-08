// enemy.h: Anton Novoselov @ 2017
// Excercise #12 from Stroustrup`s book
// Topic: vectors and arrays (game "Hunt the Wumpus")
// Description: enemy abstract class

#ifndef ENEMY_H
#define ENEMY_H

#include "subject.h"

namespace anshub {

class Enemy : public Subject
{
public:
  explicit Enemy(Labyrinth* cave)
  : Subject(cave)
  { type_ = ENEMY; }
  // Enemy(Labyrinth* cave) : Subject(cave) { CheckIn(); type_ = ENEMY; }
  ~Enemy(){ }
  // ~Enemy() { CheckOut(); }
  // Person ExamineRoom() const override;
  virtual std::string FeelsRepresent() const =0;
protected:
  // void CheckIn() override { curr_room_->enemy_ = this; }
  // void CheckOut() override { curr_room_->enemy_ = nullptr; }
};

}

#endif
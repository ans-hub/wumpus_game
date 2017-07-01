
#ifndef MVC_SET_MODEL
#define MVC_SET_MODEL

#include <stdexcept>
#include <string>

#include "ui/abc/observable.h"

namespace mvc_set {
 
class Model : public Observable<Enum::Actions, int&, int&>
{
public:
  Model();
  void StartGame();
  void PlayerTurn();
  void EnemyTurn();
private:
  Labyrinth cave_;
  Wump wump_;
  Bat bats_;
  Pit pit_;
  Player player_;
  bool game_over_;

  void BuildNewCave();
};

}  // namespace mvc_set

#endif  // MVC_SET_MODEL
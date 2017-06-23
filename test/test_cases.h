// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: interface for test-cases of wumpus_game
//
// Note: some testing functions which have returned values, ruturns not
// bool but int since we needs be consistence with behavor of main().
// Returns values of main() will be used in automated tests. 

#ifndef TEST_CASES_H
#define TEST_CASES_H

#include <iostream>
#include <algorithm>
#include "3rdparty/test_toolkit.h"
#include "3rdparty/rand_toolkit.h"

#include "labyrinth.h"
#include "room.h"
#include "subject.h"
#include "enemy.h"
#include "player.h"
#include "wump.h"
#include "pit.h"
#include "bat.h"
#include "helpers.h"

namespace wumpus_game {

// Helper struct to place subject in concrete room not random

struct TestSubject : Subject
{
  TestSubject(const Labyrinth& cave, int start);
  int start_room_;
};

// Helper struct to make abstract class not abstract

struct TestEnemy : Enemy
{
  TestEnemy(const Labyrinth& cave) : Enemy(cave) { }
  std::string FeelsRepresent() const override { return ""; }
};

// Helper struct to give access to the rooms directly

struct TestCave : Labyrinth
{
  TestCave(int size) : Labyrinth(size) { }
  std::vector<Room*> GetAllRooms() const { return rooms_; }
};

// Collection of function to test behavior of wumpus_package

namespace test_labyrinth_behavior {

  int creating();

}

namespace test_subject_behavior {

  int static_moving();
  int dynamic_moving();
  int random_placing();
  int examine_room();
  int check_in_and_out_1();
  int check_in_and_out_2();

}

namespace test_player_behavior {

  int feels();
  int shot();

}

}  // namespace wumpus_game

#endif  // TEST_CASES_H
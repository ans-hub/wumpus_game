// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: interface for test-cases of wumpus_game
//

#ifndef TEST_CASES_H
#define TEST_CASES_H

#include <iostream>
#include <algorithm>

#include "3rdparty/test_toolkit.h"
#include "3rdparty/rand_toolkit.h"
#include "3rdparty/audio/audio_out.h"

#include "config.h"
#include "entities/map.h"
#include "entities/room.h"
#include "entities/subject.h"
#include "entities/enemy.h"
#include "entities/player.h"
#include "entities/wump.h"
#include "entities/pit.h"
#include "entities/bat.h"
#include "entities/level.h"
#include "entities/logic.h"
#include "entities/helpers.h"
#include "test_helpers.h"
#include "ai/ai_controller.h"
#include "gui/images.h"

namespace wumpus_game {

// Helper struct to place subject in concrete room not random

struct TestSubject : Subject
{
  TestSubject(Map* cave, int start);
};

// Helper struct to make abstract class not abstract

struct TestEnemy : Enemy
{
  TestEnemy(Map* cave) : Enemy(cave) { }
};

// Helper struct to give access to the rooms directly

struct TestCave : Map
{
  TestCave(int size) : Map(size) { }
  std::vector<Room*> GetAllRooms() const { return rooms_; }
};

// Collection of function to test behavior of wumpus_package

namespace test_map_behavior {

  int creating();
  int move_semantic();

}

namespace test_level_behavior {

  int creating();
  int move_semantic();

}

namespace test_subject_behavior {

  int creating_and_placing();
  int move_semantic();
  int static_moving();
  int dynamic_moving();
  int random_placing();
  int examine_room();
  int check_in_and_out_1();
  int check_in_and_out_2();

}

namespace test_player_behavior {

  int move_semantic();
  int feels();

}

namespace test_logic_behavior {

  int init();
  int for_exceptions();

}

namespace test_experiments {

  int experimental();

}

namespace test_leaks {

  void images_class();
  void audio_out_class();

}

}  // namespace wumpus_game

#endif  // TEST_CASES_H
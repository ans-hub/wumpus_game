// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: main app for testing wumpus_game package

#include "test_cases.h"

int main()
{
  using namespace wumpus_game;
  
  int status{0};
  rand_toolkit::start_rand();

  status += test_map_behavior::creating();
  //status += test_map_behavior::move_semantic();			// see note #1

  status += test_level_behavior::creating();
  status += test_level_behavior::move_semantic();

  status += test_subject_behavior::creating_and_placing();
  status += test_subject_behavior::move_semantic();
  status += test_subject_behavior::static_moving();
  status += test_subject_behavior::dynamic_moving();
  status += test_subject_behavior::random_placing();
  status += test_subject_behavior::examine_room();
  status += test_subject_behavior::check_in_and_out_1();
  status += test_subject_behavior::check_in_and_out_2();
  
  //status += test_player_behavior::move_semantic();		// see note #1
  status += test_player_behavior::feels();

  status += test_logic_behavior::init();
  status += test_logic_behavior::for_exceptions();

  test_leaks::images_class();
  test_leaks::audio_out_class();

  return status; 
}

// Note #1 : disabled, need to redesign
// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: main game

#include <iostream>

#include "3rdparty/rand_toolkit.h"

#include "entities/logic.h"
#include "cli/view.h"
#include "cli/controller.h"
#include "ai/controller.h"
#include "gui/windows.h"
#include "gui/media.h"
#include "gui/controller.h"
#include "audio/audio_out.h"
#include "scores/scores.h"
#include "gui/images/images.h"
#include "settings/config.h"

void preload_background_music(wumpus_game::AudioOut& sounds)
{
  using namespace wumpus_game;

  for (int i = 1; i <= config::levels_max; ++i) 
    sounds.Load(config::GetBgMusic(i), true);
}

void start_random_generator()
{
  rand_toolkit::start_rand();
}

int main()
{
  using namespace wumpus_game;
  
  Logic         logic   {};
  AudioOut      sounds  {};
  Images        images  {};
  Windows       gui     {sounds, images};

  GuiController ctrl    {logic, gui};
  Media         media   {logic, gui, sounds};
  CliView       cerr    {std::cout, logic};
  Scores        scores  {logic};

  logic.RegisterObserver(media);
  logic.RegisterObserver(scores);
  logic.RegisterObserver(cerr);

  preload_background_music(sounds);
  start_random_generator();

  return ctrl.RunModel();
}


// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: main game

#include <iostream>

#include "entities/logic.h"
#include "cli/view.h"
#include "cli/controller.h"
#include "ai/controller.h"
#include "gui/windows.h"
#include "gui/media.h"
#include "gui/controller.h"
#include "audio/audio_out.h"
#include "scores/scores.h"
#include "settings/config.h"

int main()
{
  using namespace wumpus_game;

  const Config  config  {};
  
  Logic         logic   {config};
  AudioOut      sounds  {config};
  Windows       gui     {config, sounds};

  GuiController ctrl    {config, logic, gui};
  Media         media   {config, logic, gui, sounds};
  Scores        scores  {config, logic};

  logic.RegisterObserver(media);
  logic.RegisterObserver(scores);

  return ctrl.RunModel();
}


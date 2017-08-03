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
#include "gui/view.h"
#include "gui/controller.h"
#include "audio/game_sounds.h"
// #include "scores/game_scores.h"

int main()
{
  using namespace wumpus_game;

  Logic         logic {};
  Windows       windows {};

  GuiView       view  {windows, logic};
  CliView       view2 {std::cout, logic};
  GuiController ctrl  {windows, logic};
  GameSounds    audio {logic};
  // GameScores    scores{ }

  logic.RegisterObserver(view);
  logic.RegisterObserver(view2);
  logic.RegisterObserver(audio);
  // logic.RegisterObserver(scores);

  ctrl.RunModel();

  return 0;
}


  // Logic         logic {};
  // Settings      settings {};
  // Windows       windows {};

  // Sounds      audio   {};
  // Windows     gui     {};
  // Media       media   {gui, audio, logic};
  // Scores      scores  {};
  // Controller  ctrl    {gui, logic};

  // logic.RegisterObserver(media);
  // logic.RegisterObserver(scores);

  // gui.UseAudio(audio);
  // gui.VoiceEvents();

  // ctrl.SetControls(gui);
  // ctrl.RunModel();
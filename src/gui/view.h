// Package: wumpus_game (v0.9)
// Description: https://github.com/ans-hub/wumpus_game
// Author: Anton Novoselov, 2017
// File: gui view of game logic

// Short work principle : GuiView as derived class from Observer is push
// recieved events into the queue. Extracting events from queue is executed
// by timer callback function every n mseconds. This callback sets in
// constructor.
//
// Callback function calls member function, which checks, if system is ready
// thus events can be processed. This feature need for cases, for example,
// when Logic state is changed, but animation of widget, based on previous
// state, still in progress

#ifndef GUI_VIEW_H
#define GUI_VIEW_H

#include <string>
#include <queue>

#include "3rdparty/observer.h"

#include "gui/windows.h"
#include "entities/logic.h"
#include "entities/helpers.h"

#include "enums/enums.h"
#include "config.h"

namespace wumpus_game {

class GuiView : public mvc_set::Observer<Event>
{
public:
  using RoomEvent = std::pair<Event, int>;
  using Events = std::queue<RoomEvent>;

  GuiView(const Logic&, Windows&);
  ~GuiView() { }

private:
  const Logic&    model_;
  Windows&        gui_;
  Events          events_;
  
  bool IncomingNotify(Event) override;    // register event
  void ProcessNextEvent();                // get event from queue
  void ExecuteEvent(Event, int);          // execute concrete event

  static void cb_process_next_event(void*);
};

namespace gui_helpers {

  void RefreshInfoWidget(Windows&, const Logic&);
  void EnableFormButtons(Windows&);
  void DisableFormButtons(Windows&);
  void ShowLevel(Windows&, const Logic&);
  void HideLevel(Windows&, const Logic&);
  void ShowErrorRoom(Windows&);
  void ShowPlayerPositionInstantly(Windows&, const Logic&);
  void ShowPlayerMovement(Windows&, int);
  void ShowBatsMovement(Windows&, int);
  void ShowPlayerShot(Windows&);
  void ShowHaventArrows(Windows&);
  void ShowFeels(Windows&, const Logic&, int);
  void ShowGameOver(Windows&, const Logic&);
  void ShowKilledOneWump(Windows&);
  void ShowGuidePosition(Windows&, const Logic&, int room);
  void MarkRoomAsVisited(Windows&, const Logic&, int room);

}  // namespace gui_helpers

}  // namespace wumpus_game

#endif // GUI_VIEW_H
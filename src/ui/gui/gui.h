
#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Window.H>

#include <string>
#include <sstream>

#include "../abc/observer.h"
#include "../../model.h"
#include "../../messages.h"

namespace mvc_set {

struct Gui
: public Fl_Window
, Observer<int&, int&>
, Observer<Messages::Actions>
{
  Gui(Model& model);
  ~Gui();

  // Interface to Controller functions

  bool IncomingNotify(int& n, int& m) const override;

  // Interface to View function

  bool IncomingNotify(Messages::Actions n) const override;
  
private:

  void StartGame();
  void EnableButtons();
  void DisableButtons() const;

  // Data members

  Model&          model_;
  Fl_Window*      window_;
  Fl_Button*      btn_start_;
  Fl_Button*      btn_send_;
  Fl_Output*      output_;
  Fl_Value_Input* input_;

  // Callbacks

  static void cb_btnstart(Fl_Widget* widget, void* gui)
  {
    ((Gui*)gui)->EnableButtons();
    ((Gui*)gui)->StartGame();
  }

};

}
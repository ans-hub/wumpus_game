// Form preview

#include "form.h"

int main()
{
  Fl_Double_Window* wnd = make_window();
  wnd->end();
  wnd->show();
  Fl::run();

  return 0;
}
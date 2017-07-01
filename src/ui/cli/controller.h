
#ifndef MVCSET_CLI_CTRL
#define MVCSET_CLI_CTRL

#include <istream>

#include "../abc/observer.h"
#include "../../model.h"

namespace mvc_set {

class CliController : public Observer<int&, int&>
{
public:
  CliController(std::istream& ist) : istream_{ist} { }
  ~CliController() { }
  bool IncomingNotify(int& n, int& m) const override;
private:
  std::istream& istream_;
};

}  // namespace mvc_set

#endif  // MVCSET_CLI_CTRL
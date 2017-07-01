
#ifndef MVCSET_CLI_VIEW
#define MVCSET_CLI_VIEW

#include <ostream>

#include "../abc/observer.h"
#include "../../model.h"
#include "../../messages.h"

namespace mvc_set {

struct CliView : public Observer<Messages::Actions>
{
  CliView(std::ostream& ost, Model& model)
  : ostream_{ost}
  , model_{model} { }
  ~CliView() { }
  bool IncomingNotify(Messages::Actions n) const override;
private:
  std::ostream& ostream_;
  Model& model_;
};

} // namespace mvc_set

#endif // MVCSET_CLI_VIEW
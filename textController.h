#ifndef TEXT_CONTROLLER_H
#define TEXT_CONTROLLER_H

#include "controller.h"
#include "userAction.h"
#include <string>

class TextController : public Controller {
  UserAction action() override;
  std::string input() override;
};

#endif

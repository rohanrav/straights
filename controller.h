#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>

#include "userAction.h"

class Controller {
  virtual UserAction action() = 0;
  virtual std::string input() = 0;

 public:
  UserAction getAction();
  std::string getInput();
  virtual ~Controller() = default;
};

#endif

#ifndef _USER_ACTION_H_
#define _USER_ACTION_H_
#include <string>

#include "action.h"

struct UserAction {
  Action action;
  std::string data;
  UserAction(Action action, std::string data) : action{action}, data{data} {};
};

#endif

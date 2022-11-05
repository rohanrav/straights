#include "controller.h"

#include <string>

UserAction Controller::getAction() { return action(); }

std::string Controller::getInput() { return input(); }

#include "textController.h"

#include <iostream>
#include <string>

#include "action.h"
#include "userAction.h"

std::string TextController::input() {
  std::string inp;
  std::cin >> inp;
  return inp;
}

UserAction TextController::action() {
  while (true) {
    std::string mainCommand;
    std::cin >> mainCommand;

    if (mainCommand == "play") {
      std::string secondCommand;
      std::cin >> secondCommand;
      return UserAction{Action::PLAY, secondCommand};
      break;
    } else if (mainCommand == "discard") {
      std::string secondCommand;
      std::cin >> secondCommand;
      return UserAction{Action::DISCARD, secondCommand};
      break;
    } else if (mainCommand == "deck") {
      return UserAction{Action::DECK, ""};
      break;
    } else if (mainCommand == "quit") {
      return UserAction{Action::QUIT, ""};
      break;
    } else if (mainCommand == "ragequit") {
      return UserAction{Action::RAGEQUIT, ""};
      break;
    } else {
      continue;
    }
  }

  return UserAction{Action::QUIT, "ERROR"};
}

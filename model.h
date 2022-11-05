#ifndef _MODEL_H_
#define _MODEL_H_
#include <memory>
#include <string>
#include <vector>

#include "controller.h"
#include "userAction.h"
#include "view.h"

class Model {
  std::vector<std::unique_ptr<View>> views;
  std::unique_ptr<Controller> control;

 protected:
  void addView(std::unique_ptr<View> v);
  void addController(std::unique_ptr<Controller> c);
  bool hasController();

 public:
  Model();
  ~Model();
  void updateViews(const std::string& s);
  void updateMViews(const std::string& s);
  void displayViews();
  UserAction getAction();
  std::string getInput();
};

#endif

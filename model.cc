#include "model.h"

#include <memory>
#include <vector>

#include "controller.h"
#include "userAction.h"
#include "view.h"

Model::Model() {}
Model::~Model() {}

UserAction Model::getAction() { return control->getAction(); }

void Model::updateViews(const std::string &s) {
  for (auto &view : views) {
    view->update(s);
  }
}

void Model::updateMViews(const std::string &s) {
  for (auto &view : views) {
    view->updateM(s);
  }
}

void Model::displayViews() {
  for (auto &view : views) {
    view->updateView();
  }
}

void Model::addView(std::unique_ptr<View> v) {
  views.emplace_back(std::move(v));
}

void Model::addController(std::unique_ptr<Controller> c) {
  control = std::move(c);
}

bool Model::hasController() { return control != nullptr; }

std::string Model::getInput() { return control->getInput(); }

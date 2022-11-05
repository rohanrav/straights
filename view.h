#ifndef VIEW_H
#define VIEW_H

#include <string>

class View {
 public:
  virtual ~View() = default;
  virtual void update(std::string msg) = 0;
  virtual void updateView() = 0;
  virtual void updateM(std::string msg) = 0;
};

#endif

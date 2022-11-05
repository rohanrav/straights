#ifndef _TEXTVIEW_H_
#define _TEXTVIEW_H_
#include "view.h"

class StraightsModel;

class TextView : public View {
  std::ostream& out;
  StraightsModel& model;

 public:
  TextView(StraightsModel& model);
  void update(std::string msg) override;
  void updateView() override;
  void updateM(std::string msg) override;
};

#endif

#ifndef CARD_ERROR_H
#define CARD_ERROR_H

class CardError {
  std::string errMsg;

 public:
  CardError(const std::string& errMsg) : errMsg{errMsg} {};
};

#endif

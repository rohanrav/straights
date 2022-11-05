#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <memory>
#include <vector>

#include "card.h"
#include "userAction.h"

class Player {
 protected:
  int totalPoints, roundPoints;
  std::shared_ptr<std::vector<Card>> hand;
  std::shared_ptr<std::vector<Card>> discards;

 public:
  std::string PLAYER_TYPE;
  Player(std::string playerType, std::unique_ptr<std::vector<Card>> hand);
  ~Player();
  void addNewHand(std::unique_ptr<std::vector<Card>> hand);
  int getTotalPoints();
  void increaseTotalPoints(int points);
  int getRoundPoints();
  void increaseRoundPoints(int points);
  std::shared_ptr<std::vector<Card>> getPlayerHand();
  std::vector<Card> getPlayerLegalMoves(
      std::shared_ptr<std::vector<std::vector<Card>>> pile);
  std::shared_ptr<std::vector<Card>> getPlayerDiscards();
  bool discardCard(std::shared_ptr<std::vector<std::vector<Card>>> pile,
                   Card card);
  bool playCard(std::shared_ptr<std::vector<std::vector<Card>>> pile,
                Card card);
};

#endif

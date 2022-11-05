#ifndef _STRAIGHTS_MODEL_H_
#define _STRAIGHTS_MODEL_H_
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "card.h"
#include "model.h"
#include "player.h"

class StraightsModel : public Model {
  int seed;
  int currentPlayer;
  const std::string HUMAN_PLAYER = "HUMAN_PLAYER";
  const std::string COMPUTER_PLAYER = "COMPUTER_PLAYER";
  std::vector<std::unique_ptr<Player>> players;
  std::shared_ptr<std::vector<std::vector<Card>>> pile;
  std::unique_ptr<std::vector<Card>> deck;
  void nextPlayer();

 public:
  StraightsModel(int seed);
  ~StraightsModel();
  void play();
  int getTotalPoints();
  void increaseTotalPoints(int points);
  int getRoundPoints();
  void increaseRoundPoints(int points);
  std::shared_ptr<std::vector<std::vector<Card>>> getPile();
  std::shared_ptr<std::vector<Card>> getPlayerHand();
  std::vector<Card> getPlayerLegalMoves();
  std::shared_ptr<std::vector<Card>> getPlayerDiscards();
};

#endif

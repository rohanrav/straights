#include "straightsModel.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <vector>

#include "action.h"
#include "card.h"
#include "player.h"
#include "suit.h"
#include "textController.h"
#include "textView.h"

StraightsModel::StraightsModel(int seed)
    : Model(), seed{seed}, currentPlayer{0} {
  const std::string CARD_RANK = "A23456789TJQK";
  const std::string CARD_SUIT = "CDHS";
  deck = std::make_unique<std::vector<Card>>();

  for (const char& s : CARD_SUIT) {
    for (const char& r : CARD_RANK) {
      deck->emplace_back(Card{r, s});
    }
  }

  pile = std::make_shared<std::vector<std::vector<Card>>>();
  pile->emplace_back(std::vector<Card>());
  pile->emplace_back(std::vector<Card>());
  pile->emplace_back(std::vector<Card>());
  pile->emplace_back(std::vector<Card>());
}

StraightsModel::~StraightsModel() {}

void StraightsModel::nextPlayer() {
  if (currentPlayer < 3)
    ++currentPlayer;
  else if (currentPlayer >= 3)
    currentPlayer = 0;
}

void StraightsModel::play() {
  addController(std::move(std::make_unique<TextController>()));
  addView(std::move(std::make_unique<TextView>(*this)));

  std::default_random_engine rng{seed};
  std::shuffle(deck->begin(), deck->end(), rng);

  Card firstCard{7, 'S'};
  for (int i = 0; i < 4; ++i) {
    std::unique_ptr<std::vector<Card>> phand =
        std::make_unique<std::vector<Card>>(deck->begin() + (i * 13),
                                            deck->begin() + ((i + 1) * 13));
    auto iter = std::find_if(phand->begin(), phand->end(),
                             [&firstCard](Card& c) { return firstCard == c; });

    if (iter != phand->end()) currentPlayer = i;
    updateViews("Is Player" + std::to_string(i + 1) +
                " a human (h) or a computer (c)?");
    const std::string playerType = getInput();
    const std::string playerTypeFormatted =
        playerType == "h" ? HUMAN_PLAYER : COMPUTER_PLAYER;
    players.emplace_back(std::move(
        std::make_unique<Player>(playerTypeFormatted, std::move(phand))));
  }

  int roundCounter = 0;
  int turnCounter = 0;
  bool runGame = true;
  while (runGame) {
    bool deckHit = false;
    while (turnCounter < 52) {
      if (turnCounter == 0 && !deckHit) {
        updateViews("A new round begins. It’s Player" +
                    std::to_string(currentPlayer + 1) + "’s turn to play.");
      }

      if (players.at(currentPlayer)->PLAYER_TYPE == COMPUTER_PLAYER) {
        displayViews();
        std::vector<Card> legalPlays = getPlayerLegalMoves();
        if (legalPlays.size() > 0) {
          Card py{legalPlays.at(0).getRank(), legalPlays.at(0).getSuitChar()};
          players.at(currentPlayer)->playCard(pile, py);
          std::string s(1, py.getSym());
          std::string c(1, py.getSuitChar());
          updateViews("Player" + std::to_string(currentPlayer + 1) + " plays " +
                      s + c + ".");
        } else {
          auto hand = getPlayerHand();
          Card py{hand->at(0).getRank(), hand->at(0).getSuitChar()};
          players.at(currentPlayer)->discardCard(pile, py);
          std::string s(1, py.getSym());
          std::string c(1, py.getSuitChar());
          updateViews("Player " + std::to_string(currentPlayer + 1) +
                      " discards " + s + c + ".");
        }
        nextPlayer();
        ++turnCounter;
      } else {
        if (!deckHit) displayViews();
        deckHit = false;

        UserAction a = getAction();
        if (a.action == Action::PLAY) {
          Card py{a.data};
          if (players.at(currentPlayer)->playCard(pile, py)) {
            updateViews("Player" + std::to_string(currentPlayer + 1) +
                        " plays " + a.data + ".");
          } else {
            updateViews("This is not a legal play.");
            deckHit = true;
          }
        } else if (a.action == Action::DISCARD) {
          Card py{a.data};
          if (players.at(currentPlayer)->discardCard(pile, py)) {
            updateViews("Player " + std::to_string(currentPlayer + 1) +
                        " discards " + a.data + ".");
          } else {
            updateViews("You have a legal play. You may not discard.");
            deckHit = true;
          }
        } else if (a.action == Action::DECK) {
          deckHit = true;
          for (int j = 0; j < 52; j += 13) {
            for (auto it = deck->begin() + j; it != deck->begin() + j + 13;
                 ++it) {
              std::string s(1, it->getSym());
              std::string c(1, it->getSuitChar());
              updateMViews(s + c + " ");
            }
            updateViews("");
          }
        } else if (a.action == Action::QUIT) {
          runGame = false;
          break;
        } else if (a.action == Action::RAGEQUIT) {
          deckHit = true;
          updateViews("Player" + std::to_string(currentPlayer + 1) +
                      " ragequits. A computer will now take over.");
          players.at(currentPlayer)->PLAYER_TYPE = COMPUTER_PLAYER;
        }

        if (!deckHit) {
          nextPlayer();
          ++turnCounter;
        }
      }
    }

    int counter = 0;
    std::vector<int> scores;
    for (auto& player : players) {
      updateMViews("Player" + std::to_string(counter + 1) + "’s discards: ");

      for (auto d = player->getPlayerDiscards()->begin();
           d != player->getPlayerDiscards()->end(); ++d) {
        std::string s(1, d->getSym());
        std::string c(1, d->getSuitChar());
        updateMViews(s + c + " ");
      }
      updateViews("");
      updateMViews("Player" + std::to_string(counter + 1) +
                   "’s score: " + std::to_string(player->getTotalPoints()) +
                   " + " + std::to_string(player->getRoundPoints()) + " = " +
                   std::to_string(
                       (player->getRoundPoints() + player->getTotalPoints())));
      updateViews("");
      scores.emplace_back(player->getRoundPoints() + player->getTotalPoints());
      ++counter;
    }

    std::vector<int> winners;
    int max = 0;
    int index = 0;
    for (auto it = scores.begin(); it != scores.end(); ++it) {
      if (*it > max) {
        max = *it;
      }
      ++index;
    }

    int min = scores.at(0);
    index = 0;
    int lindex = 0;
    for (auto it = scores.begin(); it != scores.end(); ++it) {
      if (*it < min) {
        min = *it;
        lindex = index;
      }
      ++index;
    }

    if (max > 80) {
      updateViews("Player" + std::to_string(lindex + 1) + " wins!");
      break;
    } else {
      std::shuffle(deck->begin(), deck->end(), rng);
      Card firstCard{7, 'S'};
      for (int i = 0; i < 4; ++i) {
        std::unique_ptr<std::vector<Card>> phand =
            std::make_unique<std::vector<Card>>(deck->begin() + (i * 13),
                                                deck->begin() + ((i + 1) * 13));

        auto iter =
            std::find_if(phand->begin(), phand->end(),
                         [&firstCard](Card& c) { return firstCard == c; });

        if (iter != phand->end()) currentPlayer = i;
        players.at(i)->addNewHand(std::move(phand));

        pile = std::make_shared<std::vector<std::vector<Card>>>();
        pile->emplace_back(std::vector<Card>());
        pile->emplace_back(std::vector<Card>());
        pile->emplace_back(std::vector<Card>());
        pile->emplace_back(std::vector<Card>());
      }
    }

    if (!runGame) break;
    ++roundCounter;
    turnCounter = 0;
  }
}

int StraightsModel::getTotalPoints() {
  return players.at(currentPlayer)->getTotalPoints();
}

void StraightsModel::increaseTotalPoints(int points) {
  players.at(currentPlayer)->increaseTotalPoints(points);
}

int StraightsModel::getRoundPoints() {
  return players.at(currentPlayer)->getRoundPoints();
}

void StraightsModel::increaseRoundPoints(int points) {
  players.at(currentPlayer)->increaseRoundPoints(points);
}

std::shared_ptr<std::vector<std::vector<Card>>> StraightsModel::getPile() {
  return pile;
}

std::shared_ptr<std::vector<Card>> StraightsModel::getPlayerHand() {
  return players.at(currentPlayer)->getPlayerHand();
}

std::vector<Card> StraightsModel::getPlayerLegalMoves() {
  return players.at(currentPlayer)->getPlayerLegalMoves(pile);
}

std::shared_ptr<std::vector<Card>> StraightsModel::getPlayerDiscards() {
  return players.at(currentPlayer)->getPlayerDiscards();
}

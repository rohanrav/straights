#include "player.h"

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

#include "card.h"
#include "player.h"
#include "suit.h"
#include "userAction.h"

Player::Player(std::string playerType, std::unique_ptr<std::vector<Card>> hand)
    : totalPoints{0}, roundPoints{0}, PLAYER_TYPE{playerType} {
  this->hand = std::make_shared<std::vector<Card>>();
  this->discards = std::make_shared<std::vector<Card>>();

  for (auto it = hand->begin(); it != hand->end(); ++it) {
    this->hand->emplace_back(*it);
  }
}

Player::~Player() {}

void Player::addNewHand(std::unique_ptr<std::vector<Card>> hand) {
  totalPoints += roundPoints;
  roundPoints = 0;
  this->hand->clear();
  this->discards->clear();
  for (auto it = hand->begin(); it != hand->end(); ++it) {
    this->hand->emplace_back(*it);
  }
}

int Player::getTotalPoints() { return totalPoints; }

void Player::increaseTotalPoints(int points) { totalPoints += points; }

int Player::getRoundPoints() { return roundPoints; }

void Player::increaseRoundPoints(int points) { roundPoints += points; }

std::shared_ptr<std::vector<Card>> Player::getPlayerHand() { return hand; }

std::vector<Card> Player::getPlayerLegalMoves(
    std::shared_ptr<std::vector<std::vector<Card>>> pile) {
  auto legal = std::make_unique<std::vector<Card>>();
  for (auto it = pile->begin(); it != pile->end(); ++it) {
    for (auto p = it->begin(); p != it->end(); ++p) {
      if (p->getRank() - 1 >= 1) {
        legal->emplace_back(Card{p->getRank() - 1, p->getSuitChar()});
      }

      if (p->getRank() + 1 <= 13) {
        legal->emplace_back(Card{p->getRank() + 1, p->getSuitChar()});
      }
    }
  }

  legal->emplace_back(Card{"7S"});
  legal->emplace_back(Card{"7D"});
  legal->emplace_back(Card{"7C"});
  legal->emplace_back(Card{"7H"});

  legal->erase(std::unique(legal->begin(), legal->end()), legal->end());
  std::vector<Card> legalHandLocal;
  std::sort(legal->begin(), legal->end());
  std::sort(hand->begin(), hand->end());
  std::set_intersection(legal->begin(), legal->end(), hand->begin(),
                        hand->end(), std::back_inserter(legalHandLocal));
  return legalHandLocal;
}

std::shared_ptr<std::vector<Card>> Player::getPlayerDiscards() {
  return discards;
}

bool Player::discardCard(std::shared_ptr<std::vector<std::vector<Card>>> pile,
                         Card card) {
  std::vector<Card> legalPlays = getPlayerLegalMoves(pile);
  if (legalPlays.size() > 0)
    return false;
  else {
    discards->emplace_back(card);
    increaseRoundPoints(card.getRank());
    hand->erase(std::remove_if(hand->begin(), hand->end(),
                               [&card](Card &c) { return card == c; }),
                hand->end());
    return true;
  }
}

bool Player::playCard(std::shared_ptr<std::vector<std::vector<Card>>> pile,
                      Card card) {
  std::vector<Card> legalPlays = getPlayerLegalMoves(pile);
  auto iter = std::find_if(legalPlays.begin(), legalPlays.end(),
                           [&card](Card &c) { return card == c; });

  if (iter != legalPlays.end()) {
    hand->erase(std::remove_if(hand->begin(), hand->end(),
                               [&card](Card &c) { return card == c; }),
                hand->end());

    Suit suit = card.getSuit();
    if (suit == Suit::CLUBS) {
      pile->at(0).emplace_back(card);
    } else if (suit == Suit::DIAMONDS) {
      pile->at(1).emplace_back(card);
    } else if (suit == Suit::HEARTS) {
      pile->at(2).emplace_back(card);
    } else {
      pile->at(3).emplace_back(card);
    }
    return true;
  }
  return false;
}

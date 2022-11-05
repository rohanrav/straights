#include "textView.h"

#include <iostream>
#include <memory>

#include "straightsModel.h"

TextView::TextView(StraightsModel &model) : model{model}, out{std::cout} {}

void TextView::update(std::string msg) { out << msg << std::endl; }

void TextView::updateView() {
  std::shared_ptr<std::vector<std::vector<Card>>> piles = model.getPile();
  std::shared_ptr<std::vector<Card>> hand = model.getPlayerHand();
  std::vector<Card> legalMoves = model.getPlayerLegalMoves();

  out << "Cards on the table:" << std::endl;
  out << "Clubs:";
  for (auto &card : piles->at(0)) {
    out << " " << card;
  }
  out << std::endl;

  out << "Diamonds:";
  for (auto &card : piles->at(1)) {
    out << " " << card;
  }
  out << std::endl;

  out << "Hearts:";
  for (auto &card : piles->at(2)) {
    out << " " << card;
  }
  out << std::endl;

  out << "Spades:";
  for (auto &card : piles->at(3)) {
    out << " " << card;
  }
  out << std::endl;

  out << "Your hand:";
  for (auto card = hand->begin(); card != hand->end(); ++card) {
    out << " " << *card;
  }
  out << std::endl;

  out << "Legal plays:";
  for (auto card = legalMoves.begin(); card != legalMoves.end(); ++card) {
    out << " " << *card;
  }
  out << std::endl;
}

void TextView::updateM(std::string msg) { out << msg; }

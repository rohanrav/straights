#include "card.h"

#include <iostream>
#include <map>

#include "cardError.h"
#include "suit.h"

Card::Card(int rank, char suit) {
  createMapping();
  this->sym = rankToSym[rank];
  this->rank = rank;
  this->suit = getSuitFromChar(suit);
}

Card::Card(char sym, char suit) {
  createMapping();
  this->sym = sym;
  this->rank = symToRank[sym];
  this->suit = getSuitFromChar(suit);
}

Card::Card(std::string card) {
  createMapping();
  sym = card[0];
  rank = symToRank[sym];
  suit = getSuitFromChar(card[1]);
}

char Card::getSuitChar() const {
  if (getSuit() == Suit::CLUBS) {
    return 'C';
  } else if (getSuit() == Suit::DIAMONDS) {
    return 'D';
  } else if (getSuit() == Suit::HEARTS) {
    return 'H';
  } else {
    return 'S';
  }
}

void Card::createMapping() {
  this->symToRank['A'] = 1;
  this->symToRank['2'] = 2;
  this->symToRank['3'] = 3;
  this->symToRank['4'] = 4;
  this->symToRank['5'] = 5;
  this->symToRank['6'] = 6;
  this->symToRank['7'] = 7;
  this->symToRank['8'] = 8;
  this->symToRank['9'] = 9;
  this->symToRank['T'] = 10;
  this->symToRank['J'] = 11;
  this->symToRank['Q'] = 12;
  this->symToRank['K'] = 13;

  this->rankToSym[1] = 'A';
  this->rankToSym[2] = '2';
  this->rankToSym[3] = '3';
  this->rankToSym[4] = '4';
  this->rankToSym[5] = '5';
  this->rankToSym[6] = '6';
  this->rankToSym[7] = '7';
  this->rankToSym[8] = '8';
  this->rankToSym[9] = '9';
  this->rankToSym[10] = 'T';
  this->rankToSym[11] = 'J';
  this->rankToSym[12] = 'Q';
  this->rankToSym[13] = 'K';
}

int Card::getRank() const { return rank; }

Suit Card::getSuit() const { return suit; }

char Card::getSym() const { return sym; }

Suit Card::getSuitFromChar(char suit) {
  if (suit == 'C') {
    return Suit::CLUBS;
  } else if (suit == 'D') {
    return Suit::DIAMONDS;
  } else if (suit == 'H') {
    return Suit::HEARTS;
  } else if (suit == 'S') {
    return Suit::SPADES;
  } else {
    throw CardError{"Incorrect card suit given!"};
  }
}

std::ostream& operator<<(std::ostream& out, const Card& card) {
  char suit;
  if (card.getSuit() == Suit::CLUBS) {
    suit = 'C';
  } else if (card.getSuit() == Suit::DIAMONDS) {
    suit = 'D';
  } else if (card.getSuit() == Suit::HEARTS) {
    suit = 'H';
  } else {  // SPADES
    suit = 'S';
  }

  out << card.getSym() << suit;
  return out;
}

bool operator==(const Card& lhs, const Card& rhs) {
  return ((lhs.getRank() == rhs.getRank()) && (lhs.getSuit() == rhs.getSuit()));
}

bool operator<(const Card& lhs, const Card& rhs) {
  std::string l =
      std::to_string(lhs.getSym()) + std::to_string(lhs.getSuitChar());
  std::string r =
      std::to_string(rhs.getSym()) + std::to_string(rhs.getSuitChar());
  return (l < r);
}

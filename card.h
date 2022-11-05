#ifndef CARD_H
#define CARD_H
#include <cstdlib>
#include <map>

#include "suit.h"

class Card {
  std::map<char, int> symToRank;
  std::map<int, char> rankToSym;

  char sym;
  int rank;
  Suit suit;
  Suit getSuitFromChar(char suit);
  void createMapping();

 public:
  Card(int rank, char suit);
  Card(char rank, char suit);
  Card(std::string card);
  char getSym() const;
  int getRank() const;
  Suit getSuit() const;
  char getSuitChar() const;
};

bool operator==(const Card &lhs, const Card &rhs);
std::ostream &operator<<(std::ostream &out, const Card &card);
bool operator<(const Card &lhs, const Card &rhs);

#endif

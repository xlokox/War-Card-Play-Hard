#ifndef __CARD_H
#define __CARD_H
#include "Suit.h"
#include <iostream>
using std::string;

class Card {
private:
  Suit suit;
  char *rank;

public:
  Card(Suit suit, std::string rank) {
    suit = suit;
    rank = rank;
  }

  Card(const Card &other)
  {
    suit = other.suit;
    rank = other.rank;
  };

  ~Card() { delete this; };
};

#endif
#ifndef __CARD_H
#define __CARD_H
#include "Suit.h"
#include <cstring>
#include <iostream>
using std::string;

class Card {
private:
  Suit suit;
  char *rank;

public:
  Card(Suit suit, char *rank) {
    this->suit = suit;
    this->rank = rank;
  }

  Card(const Card &other) {
    suit = Suit(other.suit);
    int len = strlen(other.rank);
    rank = new char[len + 1];
    strcpy(rank, other.rank);
  };

  ~Card() { delete[] rank; };
};

#endif
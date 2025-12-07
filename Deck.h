#ifndef __DECK_H
#define __DECK_H

#include "Card.h"
#include <iostream>
using std::string;

class Deck {
private:
  int cardCount = 52;
  Card *cards; // array of Card objects

public:
  Deck() { cards = new Card[cardCount]; }

  Deck(const Deck &other) {
    cards = new Card[other.cardCount];
    for (int i = 0; i < other.cardCount; i++) {
      cards[i] = other.cards[i];
    }
  }

  // Methods
  void populateDeckFromFile(const std::string &filename);
  void addCard(Card card);
  bool isEmpty();
  Card draw();
  Deck shuffle();

  ~Deck() { delete[] cards; };
};

#endif
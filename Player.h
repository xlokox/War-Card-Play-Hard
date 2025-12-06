#ifndef __PLAYER_H
#define __PLAYER_H
#include "Deck.h"
#include <iostream>
using namespace std;

class Player {
private:
  char *name;
  Deck hand;

public:
  Player(char *n) { name = n; }
  Player(const Player &other) {
    name = other.name;
    hand = other.hand;
  }
  ~Player();

  void receiveCard(Card c);
  Card playCard();
};

#endif
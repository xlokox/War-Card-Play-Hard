#ifndef __PLAYER_H
#define __PLAYER_H
#include "Deck.h"
#include <cstring>
#include <iostream>
using namespace std;

class Player {
private:
  char *name;
  Deck hand;

public:
  Player(char *n) {
    int len = strlen(n);
    name = new char[len + 1];
    strcpy(name, n);
  }

  Player(const Player &other) {
    int len = strlen(other.name);
    name = new char[len + 1];
    strcpy(name, other.name);
    hand = other.hand;
  }

  ~Player() { delete[] name; }

  void receiveCard(Card c);
  Card playCard();
};

#endif
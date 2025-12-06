#ifndef __GAME_H
#define __GAME_H

#include "Deck.h"
#include "Player.h"

class Game {
private:
  Player *player1;
  Player *player2;
  Deck mainDeck;

public:
  Game(char *p1, char *p2) {
    *player1 = p1;
    *player2 = p2;
  };
  Game(const Game &other) {
    player1 = other.player1;
    player2 = other.player2;
    mainDeck = other.mainDeck;
  };
  ~Game() { delete this; };
  void start();
  void playRound();
  int checkWinner();
};

#endif
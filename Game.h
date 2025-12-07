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
    player1 = new Player(p1);
    player2 = new Player(p2);
  };

  Game(const Game &other) {
    player1 = new Player(*other.player1);
    player2 = new Player(*other.player2);
    mainDeck = other.mainDeck;
  };

  ~Game() {
    delete player1;
    delete player2;
  };

  void start();
  void playRound();
  int checkWinner();
};

#endif
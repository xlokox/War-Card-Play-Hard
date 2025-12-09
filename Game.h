// Names: Arad David, Daniel Knafel
// IDs: 206779597, -id-

#ifndef __GAME_H
#define __GAME_H

#include "Player.h"

class Game {
private:
  Player player1;
  Player player2;

public:
  // Constructor to initialize the game with two players
  Game(const Player &p1, const Player &p2);

  // Copy constructor for deep copying of game objects
  Game(const Game &other);

  // Assignment operator for proper memory management
  Game &operator=(const Game &other);

  // Destructor to free allocated memory
  ~Game();

  // Starts the game
  void start();

  // Plays a round of the game
  void playRound();

  // Checks and returns the winner of the game (1 for player1, 2 for player2, 0
  // for no winner yet)
  int checkWinner();
};

#endif

// Main.cpp
// Names: Arad David, Daniel Knafel
// IDs: 206779597, -id-

#include "Deck.h"
#include "Game.h"
#include "Player.h"
#include <iostream>
#include <string>

int main() {
  // Initialize the main deck for the game
  Deck mainDeck;

  std::string filename = "Cards.txt";
  // Populate the deck from the file
  mainDeck.populateDeckFromFile(filename);

  // Validate that the deck contains 52 unique cards
  if (!mainDeck.validateDeck()) {
    std::cerr << "Error: Deck validation failed! Deck must contain exactly 52 "
                 "unique cards."
              << std::endl;
    return 1;
  }

  // Shuffle the main deck before starting
  mainDeck.shuffle();

  // Create two players
  char name1[] = "Alice";
  char name2[] = "Bob";
  Player player1(name1);
  Player player2(name2);

  // Distribute cards to each player from the main deck
  bool giveToPlayer1 = true;
  while (!mainDeck.isEmpty()) {
    if (giveToPlayer1) {
      player1.receiveCard(mainDeck.draw());
    } else {
      player2.receiveCard(mainDeck.draw());
    }
    giveToPlayer1 = !giveToPlayer1;
  }

  // Initialize the game with the two players
  Game warGame(player1, player2);

  // Start the game (displays initial state)
  warGame.start();

  // Main game loop
  bool gameRunning = true;
  int roundCount = 0;
  const int MAX_ROUNDS = 10000; // Prevent infinite loops

  while (gameRunning && roundCount < MAX_ROUNDS) {
    // Play a round
    warGame.playRound();

    // Check for a winner
    int winner = warGame.checkWinner();
    if (winner != 0) {
      gameRunning = false;
      std::cout << "Player " << winner << " wins the game after " << roundCount
                << " rounds!" << std::endl;
    }

    roundCount++;
  }

  if (roundCount >= MAX_ROUNDS) {
    std::cout << "Game reached maximum rounds limit." << std::endl;
  }

  return 0;
}

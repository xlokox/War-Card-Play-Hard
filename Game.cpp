// Game.cpp
// Names: Arad David, Daniel Knafel
// IDs: 206779597, -id-

#include "Game.h"
#include "Card.h"
#include "Player.h"
#include "Suit.h"
#include <iostream>
#include <vector>

// Helper function to get suit name as string
static const char *getSuitName(Suit suit) {
  switch (suit) {
  case Hearts:
    return "Hearts";
  case Diamonds:
    return "Diamonds";
  case Clubs:
    return "Clubs";
  case Spades:
    return "Spades";
  default:
    return "Unknown";
  }
}

// Helper function to format card display
static std::string formatCard(const Card &card) {
  return std::string(card.getRank()) + " of " + getSuitName(card.getSuit());
}

// Constructor to initialize the game with two players
Game::Game(const Player &p1, const Player &p2) : player1(p1), player2(p2) {}

// Copy constructor for deep copying of game objects
Game::Game(const Game &other)
    : player1(other.player1), player2(other.player2) {}

// Assignment operator for proper memory management
Game &Game::operator=(const Game &other) {
  if (this != &other) {
    player1 = other.player1;
    player2 = other.player2;
  }
  return *this;
}

// Destructor to free allocated memory
Game::~Game() {
  // Player destructors will handle their own cleanup
}

// Starts the game
void Game::start() {
  std::cout << "\n=== WAR CARD GAME STARTED ===" << std::endl;
  std::cout << "Player 1: " << player1.getName() << " ("
            << player1.getCardCount() << " cards)" << std::endl;
  std::cout << "Player 2: " << player2.getName() << " ("
            << player2.getCardCount() << " cards)" << std::endl;
  std::cout << "Let the battles begin!\n" << std::endl;
}

// Plays a round of the game
void Game::playRound() {
  // Check if both players have cards
  if (!player1.hasCards() || !player2.hasCards()) {
    return;
  }

  // Each player reveals their top card
  Card card1 = player1.playCard();
  Card card2 = player2.playCard();

  std::cout << "--- BATTLE ---" << std::endl;
  std::cout << player1.getName() << " plays: " << formatCard(card1)
            << std::endl;
  std::cout << player2.getName() << " plays: " << formatCard(card2)
            << std::endl;

  // Collect cards that will go to the winner
  std::vector<Card> cardsToWin;
  cardsToWin.push_back(card1);
  cardsToWin.push_back(card2);

  // Compare cards
  int comparison = card1.compare(card2);
  int warCount = 0;

  // If cards are equal, we have a war
  while (comparison == 0) {
    warCount++;
    std::cout << "\n*** WAR #" << warCount << "! ***" << std::endl;
    // Check if both players have enough cards for war (need at least 4 cards: 3
    // face down, 1 face up)
    if (!player1.hasCards() || !player2.hasCards()) {
      // If a player runs out of cards during war, they lose
      // Distribute all collected cards to the player who still has cards
      if (player1.hasCards()) {
        for (size_t i = 0; i < cardsToWin.size(); i++) {
          player1.receiveCard(cardsToWin[i]);
        }
      } else if (player2.hasCards()) {
        for (size_t i = 0; i < cardsToWin.size(); i++) {
          player2.receiveCard(cardsToWin[i]);
        }
      }
      return;
    }

    // Place three cards face down (each player)
    std::cout << "Both players place 3 cards face down..." << std::endl;
    for (int i = 0; i < 3; i++) {
      if (!player1.hasCards() || !player2.hasCards()) {
        // If a player runs out during placing face-down cards, they lose
        std::cout << "ERROR: A player ran out of cards during war!"
                  << std::endl;
        if (player1.hasCards()) {
          for (size_t j = 0; j < cardsToWin.size(); j++) {
            player1.receiveCard(cardsToWin[j]);
          }
          std::cout << player1.getName()
                    << " wins by default (opponent out of cards)" << std::endl;
        } else if (player2.hasCards()) {
          for (size_t j = 0; j < cardsToWin.size(); j++) {
            player2.receiveCard(cardsToWin[j]);
          }
          std::cout << player2.getName()
                    << " wins by default (opponent out of cards)" << std::endl;
        }
        return;
      }
      Card faceDown1 = player1.playCard();
      Card faceDown2 = player2.playCard();
      cardsToWin.push_back(faceDown1);
      cardsToWin.push_back(faceDown2);
    }

    // Check if players still have cards for the face-up card
    if (!player1.hasCards() || !player2.hasCards()) {
      // If a player runs out, they lose
      if (player1.hasCards()) {
        for (size_t i = 0; i < cardsToWin.size(); i++) {
          player1.receiveCard(cardsToWin[i]);
        }
      } else if (player2.hasCards()) {
        for (size_t i = 0; i < cardsToWin.size(); i++) {
          player2.receiveCard(cardsToWin[i]);
        }
      }
      return;
    }

    // Place the fourth card face up
    Card faceUp1 = player1.playCard();
    Card faceUp2 = player2.playCard();
    cardsToWin.push_back(faceUp1);
    cardsToWin.push_back(faceUp2);

    std::cout << player1.getName() << " reveals: " << formatCard(faceUp1)
              << std::endl;
    std::cout << player2.getName() << " reveals: " << formatCard(faceUp2)
              << std::endl;

    // Compare the new face-up cards
    comparison = faceUp1.compare(faceUp2);

    if (comparison == 0) {
      std::cout << "Cards are equal again! War continues..." << std::endl;
    }
  }

  // Distribute cards to the winner
  if (comparison > 0) {
    // Player 1 wins
    for (size_t i = 0; i < cardsToWin.size(); i++) {
      player1.receiveCard(cardsToWin[i]);
    }
    std::cout << ">>> " << player1.getName() << " WINS! (" << cardsToWin.size()
              << " cards)" << std::endl;
  } else {
    // Player 2 wins
    for (size_t i = 0; i < cardsToWin.size(); i++) {
      player2.receiveCard(cardsToWin[i]);
    }
    std::cout << ">>> " << player2.getName() << " WINS! (" << cardsToWin.size()
              << " cards)" << std::endl;
  }

  // Show card counts after the round
  int p1CardsAfter = player1.getCardCount();
  int p2CardsAfter = player2.getCardCount();
  std::cout << "Card count - " << player1.getName() << ": " << p1CardsAfter
            << " | " << player2.getName() << ": " << p2CardsAfter << std::endl;
  std::cout << std::endl;
}

// Checks and returns the winner of the game
int Game::checkWinner() {
  if (!player1.hasCards() && !player2.hasCards()) {
    return 0; // Both out of cards (shouldn't happen)
  }
  if (!player1.hasCards()) {
    return 2; // Player 2 wins
  }
  if (!player2.hasCards()) {
    return 1; // Player 1 wins
  }
  return 0; // No winner yet
}

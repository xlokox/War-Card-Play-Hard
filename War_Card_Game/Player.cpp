// Player.cpp
// Names: Arad David, Daniel Knafel
// IDs: 206779597, -id-

#include "Player.h"
#include "Card.h"
#include "Deck.h"
#include <cstring>

// Constructor to initialize a player with a name
Player::Player(char *n) {
  int len = strlen(n);
  name = new char[len + 1];
  strcpy(name, n);
}

// Copy constructor for deep copying of player objects
Player::Player(const Player &other) {
  int len = strlen(other.name);
  name = new char[len + 1];
  strcpy(name, other.name);
  hand = other.hand; // Deck's copy constructor will handle deep copy
}

// Assignment operator for proper memory management
Player &Player::operator=(const Player &other) {
  if (this != &other) {
    delete[] name;
    int len = strlen(other.name);
    name = new char[len + 1];
    strcpy(name, other.name);
    hand = other.hand; // Deck's assignment operator will handle deep copy
  }
  return *this;
}

// Destructor to free allocated memory
Player::~Player() {
  delete[] name;
}

// Adds a card to the player's hand
void Player::receiveCard(Card c) {
  hand.addCardToEnd(c);
}

// Plays and returns a card from the player's hand
Card Player::playCard() {
  if (!hand.isEmpty()) {
    return hand.draw();
  }
  // Return default card if hand is empty (shouldn't happen in proper game)
  return Card();
}

// Checks if player has cards
bool Player::hasCards() const {
  return !hand.isEmpty();
}

// Getter for name
char* Player::getName() const {
  return name;
}

// Getter for card count in hand
int Player::getCardCount() const {
  return hand.getCardCount();
}

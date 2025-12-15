// Names: Arad David, Daniel Knafel
// IDs: 206779597, -id-

#ifndef __PLAYER_H
#define __PLAYER_H
#include "Deck.h"
#include <cstring>

class Player {
private:
  char *name;
  Deck hand;

public:
  // Constructor to initialize a player with a name
  Player(char *n);
  
  // Copy constructor for deep copying of player objects
  Player(const Player &other);
  
  // Assignment operator for proper memory management
  Player &operator=(const Player &other);
  
  // Destructor to free allocated memory
  ~Player();
  
  // Adds a card to the player's hand
  void receiveCard(Card c);
  
  // Plays and returns a card from the player's hand
  Card playCard();
  
  // Checks if player has cards
  bool hasCards() const;
  
  // Getter for name
  char* getName() const;
  
  // Getter for card count in hand
  int getCardCount() const;
};

#endif

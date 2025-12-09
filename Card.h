// Names: Arad David, Daniel Knafel
// IDs: 206779597, -id-

#ifndef __CARD_H
#define __CARD_H
#include "Suit.h"
#include <cstring>

class Card {
private:
  Suit suit;
  char *rank;

public:
  // Constructor to initialize a card with a suit and rank
  Card(Suit suit, char *rank);

  // Default constructor
  Card();

  // Copy constructor for deep copying of card objects
  Card(const Card &other);

  // Assignment operator for proper memory management
  Card &operator=(const Card &other);

  // Destructor to free allocated memory
  ~Card();

  // Getters
  Suit getSuit() const;
  char *getRank() const;

  // Compare two cards (returns 1 if this > other, -1 if this < other, 0 if
  // equal) Aces are high, suits are ignored
  int compare(const Card &other) const;

  // Check if two cards are equal (same suit and rank)
  bool equals(const Card &other) const;
};

#endif

// Card.cpp
// Names: Arad David, Daniel Knafel
// IDs: 206779597, -id-

#include "Card.h"
#include <cstdlib>
#include <cstring>

// Constructor to initialize a card with a suit and rank
Card::Card(Suit suit, char *rank) {
  this->suit = suit;
  int len = strlen(rank);
  this->rank = new char[len + 1];
  strcpy(this->rank, rank);
}

// Default constructor
Card::Card() {
  suit = Hearts;
  rank = new char[5];
  strcpy(rank, "Ace");
}

// Copy constructor for deep copying of card objects
Card::Card(const Card &other) {
  suit = other.suit;
  int len = strlen(other.rank);
  rank = new char[len + 1];
  strcpy(rank, other.rank);
}

// Assignment operator for proper memory management
Card &Card::operator=(const Card &other) {
  if (this != &other) {
    delete[] rank;
    suit = other.suit;
    int len = strlen(other.rank);
    rank = new char[len + 1];
    strcpy(rank, other.rank);
  }
  return *this;
}

// Destructor to free allocated memory
Card::~Card() { delete[] rank; }

// Getter for suit
Suit Card::getSuit() const { return suit; }

// Getter for rank
char *Card::getRank() const { return rank; }

// Helper function to get numeric value of rank
static int getRankValue(const char *rank) {
  if (strcmp(rank, "Ace") == 0)
    return 14;
  if (strcmp(rank, "King") == 0)
    return 13;
  if (strcmp(rank, "Queen") == 0)
    return 12;
  if (strcmp(rank, "Jack") == 0)
    return 11;
  if (strcmp(rank, "10") == 0)
    return 10;
  if (strcmp(rank, "9") == 0)
    return 9;
  if (strcmp(rank, "8") == 0)
    return 8;
  if (strcmp(rank, "7") == 0)
    return 7;
  if (strcmp(rank, "6") == 0)
    return 6;
  if (strcmp(rank, "5") == 0)
    return 5;
  if (strcmp(rank, "4") == 0)
    return 4;
  if (strcmp(rank, "3") == 0)
    return 3;
  if (strcmp(rank, "2") == 0)
    return 2;
  return 0; // Unknown rank
}

// Compare two cards (returns 1 if this > other, -1 if this < other, 0 if equal)
// Aces are high, suits are ignored
int Card::compare(const Card &other) const {
  int thisValue = getRankValue(this->rank);
  int otherValue = getRankValue(other.rank);

  if (thisValue > otherValue)
    return 1;
  if (thisValue < otherValue)
    return -1;
  return 0;
}

// Check if two cards are equal (same suit and rank)
bool Card::equals(const Card &other) const {
  return (this->suit == other.suit && strcmp(this->rank, other.rank) == 0);
}

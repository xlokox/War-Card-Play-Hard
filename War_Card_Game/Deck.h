// Names: Arad David, Daniel Knafel
// IDs: 206779597, -id-

#ifndef __DECK_H
#define __DECK_H

#include "Card.h"
#include <string>

class Deck {
private:
  Card *cards;   // array of Card objects
  int cardCount; // number of cards currently in the deck

  // Helper method to add a card to the deck
  void addCard(Card card);

public:
  // Constructor to initialize the deck
  Deck();

  // Copy constructor for deep copying of deck objects
  Deck(const Deck &other);

  // Assignment operator for proper memory management
  Deck &operator=(const Deck &other);

  // Destructor to free allocated memory
  ~Deck();

  // Shuffles the cards in the deck
  void shuffle();

  // Draws and returns the top card from the deck
  Card draw();

  // Checks if the deck is empty
  bool isEmpty() const;

  // Populates the Deck with Card objects based on data from a file
  void populateDeckFromFile(const std::string &filename);

  // Getter for card count
  int getCardCount() const;

  // Adds a card to the end of the deck (used when player wins cards)
  void addCardToEnd(Card card);

  // Validates that the deck contains exactly 52 unique cards
  bool validateDeck() const;
};

#endif

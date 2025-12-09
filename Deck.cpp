// Deck.cpp
// Names: Arad David, Daniel Knafel
// IDs: 206779597, -id-

#include "Deck.h"
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

// Constructor to initialize the deck
Deck::Deck() {
  cards = new Card[52];
  cardCount = 0;
}

// Copy constructor for deep copying of deck objects
Deck::Deck(const Deck &other) {
  cardCount = other.cardCount;
  cards = new Card[52];
  for (int i = 0; i < cardCount; i++) {
    cards[i] = other.cards[i];
  }
}

// Assignment operator for proper memory management
Deck &Deck::operator=(const Deck &other) {
  if (this != &other) {
    delete[] cards;
    cardCount = other.cardCount;
    cards = new Card[52];
    for (int i = 0; i < cardCount; i++) {
      cards[i] = other.cards[i];
    }
  }
  return *this;
}

// Destructor to free allocated memory
Deck::~Deck() { delete[] cards; }

// Helper method to add a card to the deck
void Deck::addCard(Card card) {
  if (cardCount < 52) {
    cards[cardCount] = card;
    cardCount++;
  }
}

// Shuffles the cards in the deck
void Deck::shuffle() {
  srand(time(nullptr));
  for (int i = cardCount - 1; i > 0; i--) {
    int j = rand() % (i + 1);
    Card temp = cards[i];
    cards[i] = cards[j];
    cards[j] = temp;
  }
}

// Draws and returns the top card from the deck
Card Deck::draw() {
  if (cardCount == 0) {
    // Return a default card if deck is empty (shouldn't happen in proper game)
    return Card();
  }
  Card topCard = cards[0];
  // Shift all cards left
  for (int i = 0; i < cardCount - 1; i++) {
    cards[i] = cards[i + 1];
  }
  cardCount--;
  return topCard;
}

// Checks if the deck is empty
bool Deck::isEmpty() const { return cardCount == 0; }

// Getter for card count
int Deck::getCardCount() const { return cardCount; }

// Adds a card to the end of the deck (used when player wins cards)
void Deck::addCardToEnd(Card card) {
  if (cardCount < 52) {
    cards[cardCount] = card;
    cardCount++;
  }
}

// Populates the Deck with Card objects based on data from a file
void Deck::populateDeckFromFile(const std::string &filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error: Could not open file " << filename << std::endl;
    return;
  }

  std::string line;
  while (getline(file, line) && cardCount < 52) {
    // Skip empty lines
    if (line.empty())
      continue;

    // Parse the line to extract suit and rank
    size_t commaPos = line.find(',');
    if (commaPos == std::string::npos)
      continue;

    std::string suitStr = line.substr(0, commaPos);
    std::string rankStr = line.substr(commaPos + 1);

    // Trim leading and trailing whitespace (including \r for Windows line
    // endings)
    while (!suitStr.empty() &&
           (suitStr[0] == ' ' || suitStr[0] == '\t' || suitStr[0] == '\r')) {
      suitStr = suitStr.substr(1);
    }
    while (!suitStr.empty() &&
           (suitStr.back() == ' ' || suitStr.back() == '\t' ||
            suitStr.back() == '\r')) {
      suitStr = suitStr.substr(0, suitStr.length() - 1);
    }
    while (!rankStr.empty() &&
           (rankStr[0] == ' ' || rankStr[0] == '\t' || rankStr[0] == '\r')) {
      rankStr = rankStr.substr(1);
    }
    while (!rankStr.empty() &&
           (rankStr.back() == ' ' || rankStr.back() == '\t' ||
            rankStr.back() == '\r' || rankStr.back() == '\n')) {
      rankStr = rankStr.substr(0, rankStr.length() - 1);
    }

    // Convert suit string to enum
    Suit suitEnum;
    if (suitStr == "Hearts") {
      suitEnum = Hearts;
    } else if (suitStr == "Diamonds") {
      suitEnum = Diamonds;
    } else if (suitStr == "Clubs") {
      suitEnum = Clubs;
    } else if (suitStr == "Spades") {
      suitEnum = Spades;
    } else {
      continue; // Invalid suit, skip this line
    }

    // Validate rank
    if (rankStr == "Ace" || rankStr == "2" || rankStr == "3" ||
        rankStr == "4" || rankStr == "5" || rankStr == "6" || rankStr == "7" ||
        rankStr == "8" || rankStr == "9" || rankStr == "10" ||
        rankStr == "Jack" || rankStr == "Queen" || rankStr == "King") {
      // Create a C-string for the rank
      char *rankCStr = new char[rankStr.length() + 1];
      std::strcpy(rankCStr, rankStr.c_str());

      // Create Card - it will make its own copy in the constructor
      Card card(suitEnum, rankCStr);
      addCard(card);

      // Free the temporary string since Card constructor made its own copy
      delete[] rankCStr;
    }
  }
  file.close();
}

// Validates that the deck contains exactly 52 unique cards
bool Deck::validateDeck() const {
  // Check if we have exactly 52 cards
  if (cardCount != 52) {
    return false;
  }

  // Check for duplicates by comparing each card with all others
  for (int i = 0; i < cardCount; i++) {
    for (int j = i + 1; j < cardCount; j++) {
      if (cards[i].equals(cards[j])) {
        return false; // Found a duplicate
      }
    }
  }

  return true; // All cards are unique
}

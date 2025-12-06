#include "Deck.h"
#include <cstring>
#include <fstream>
#include <string>

void Deck::populateDeckFromFile(const std::string &filename) {
  std::ifstream file(filename);
  std::string line;
  while (std::getline(file, line)) {
    // Parse the line to extract suit and rank
    size_t commaPos = line.find(',');
    if (commaPos == std::string::npos)
      continue;

    std::string suit = line.substr(0, commaPos);
    std::string rank = line.substr(commaPos + 1);

    // Trim whitespace from rank
    size_t first = rank.find_first_not_of(" \t");
    if (first != std::string::npos) {
      rank = rank.substr(first);
    }

    // Validate the extracted suit and rank
    Suit suitEnum;
    if (suit == "Hearts") {
      suitEnum = Hearts;
    } else if (suit == "Diamonds") {
      suitEnum = Diamonds;
    } else if (suit == "Clubs") {
      suitEnum = Clubs;
    } else if (suit == "Spades") {
      suitEnum = Spades;
    } else {
      continue; // Invalid suit, skip this line
    }

    if (rank == "Ace" || rank == "2" || rank == "3" || rank == "4" ||
        rank == "5" || rank == "6" || rank == "7" || rank == "8" ||
        rank == "9" || rank == "10" || rank == "Jack" || rank == "Queen" ||
        rank == "King") {
      // If valid, create a Card object and add it to the deck
      char *rankCStr = new char[rank.length() + 1];
      std::strcpy(rankCStr, rank.c_str());
      addCard(Card(suitEnum, rankCStr));
    }
  }
  file.close();
}

void Deck::addCard(Card card) 
{
  
}

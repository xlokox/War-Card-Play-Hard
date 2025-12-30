#include "Game.h"
#include "Character.h"
#include "Dagger.h"
#include "Dungeon.h"
#include "Item.h"
#include "Mage.h"
#include "Monster.h"
#include "Potion.h"
#include "Room.h"
#include "Shield.h"
#include "Sword.h"
#include "Thief.h"
#include "Wand.h"
#include "Warrior.h"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>

Game::Game() : dungeon(new Dungeon()), currentCharacter(nullptr) {}

Game::~Game() {
  delete dungeon;

  for (auto &pair : characters) {
    delete pair.second;
  }

  for (auto &pair : items) {
    delete pair.second;
  }

  for (auto &pair : monsters) {
    delete pair.second;
  }

  // Rooms are deleted by dungeon
  // No need to delete rooms here - they're owned by dungeon
}

std::vector<std::string> Game::splitString(const std::string &str) {
  std::vector<std::string> tokens;
  std::istringstream iss(str);
  std::string token;

  while (iss >> token) {
    // Skip comments
    if (token[0] == '/' && token[1] == '/') {
      break;
    }
    tokens.push_back(token);
  }

  return tokens;
}

void Game::parseAndExecute(const std::string &line) {
  // Skip empty lines and comments
  if (line.empty() ||
      (line.length() >= 2 && line[0] == '/' && line[1] == '/')) {
    return;
  }

  std::vector<std::string> tokens = splitString(line);
  if (tokens.empty()) {
    return;
  }

  std::string command = tokens[0];
  std::transform(command.begin(), command.end(), command.begin(), ::tolower);

  if (command == "create") {
    if (tokens.size() >= 3) {
      std::string type = tokens[1];
      std::transform(type.begin(), type.end(), type.begin(), ::tolower);

      if (type == "room") {
        createRoom(tokens);
      } else if (type == "warrior" || type == "mage" || type == "thief") {
        createCharacter(tokens);
      }
    }
  } else if (command == "set" && tokens.size() >= 3) {
    std::string subcommand = tokens[1];
    std::transform(subcommand.begin(), subcommand.end(), subcommand.begin(),
                   ::tolower);
    if (subcommand == "startroom") {
      setStartRoom(tokens);
    }
  } else if (command == "connect") {
    connectRooms(tokens);
  } else if (command == "place") {
    if (tokens.size() >= 2) {
      std::string placeType = tokens[1];
      if (placeType == "Item") {
        placeItem(tokens);
      } else if (placeType == "Monster") {
        placeMonster(tokens);
      }
    }
  } else if (command == "enter") {
    enterDungeon(tokens);
  } else if (command == "move") {
    moveCharacter(tokens);
  } else if (command == "fight") {
    fightMonster(tokens);
  } else if (command == "pickup") {
    pickupItem(tokens);
  }
}

void Game::createCharacter(const std::vector<std::string> &tokens) {
  if (tokens.size() < 3)
    return;

  std::string type = tokens[1];
  std::string name = tokens[2];

  std::transform(type.begin(), type.end(), type.begin(), ::tolower);

  Character *character = nullptr;
  if (type == "warrior") {
    character = new Warrior(name.c_str());
  } else if (type == "mage") {
    character = new Mage(name.c_str());
  } else if (type == "thief") {
    character = new Thief(name.c_str());
  }

  if (character) {
    characters[name] = character;
  }
}

void Game::createRoom(const std::vector<std::string> &tokens) {
  if (tokens.size() < 3)
    return;

  std::string roomName = tokens[2];
  Room *room = new Room(roomName.c_str());
  rooms[roomName] = room;
  dungeon->addRoom(room);
}

void Game::setStartRoom(const std::vector<std::string> &tokens) {
  if (tokens.size() < 3)
    return;

  std::string roomName = tokens[2];
  Room *room = rooms[roomName];
  if (room) {
    dungeon->setStartRoom(room);
  }
}

void Game::connectRooms(const std::vector<std::string> &tokens) {
  if (tokens.size() < 4)
    return;

  std::string room1Name = tokens[1];
  std::string room2Name = tokens[2];
  std::string direction = tokens[3];

  Room *room1 = rooms[room1Name];
  Room *room2 = rooms[room2Name];

  if (!room1 || !room2)
    return;

  if (direction == "North") {
    room1->connectNorth(room2);
  } else if (direction == "South") {
    room1->connectSouth(room2);
  } else if (direction == "East") {
    room1->connectEast(room2);
  } else if (direction == "West") {
    room1->connectWest(room2);
  }
}

Item *Game::createItem(const std::string &type, int h, int s, int d) {
  if (type == "Sword") {
    return new Sword("Sword", h, s, d);
  } else if (type == "Shield") {
    return new Shield("Shield", h, s, d);
  } else if (type == "Dagger") {
    return new Dagger("Dagger", h, s, d);
  } else if (type == "Wand") {
    return new Wand("Wand", h, s, d);
  } else if (type == "Potion") {
    return new Potion("Potion", h, s, d);
  }
  return nullptr;
}

void Game::placeItem(const std::vector<std::string> &tokens) {
  if (tokens.size() < 7)
    return;

  std::string itemType = tokens[2];
  std::string roomName = tokens[3];
  int h = std::stoi(tokens[4]);
  int s = std::stoi(tokens[5]);
  int d = std::stoi(tokens[6]);

  // Get default stats for the item type
  int defaultH = 0, defaultS = 0, defaultD = 0;
  if (itemType == "Sword") {
    defaultS = 5;
    defaultD = 10;
  } else if (itemType == "Dagger") {
    defaultS = 7;
    defaultD = 3;
  } else if (itemType == "Wand") {
    defaultS = 10;
    defaultD = 0;
  } else if (itemType == "Shield") {
    defaultS = 0;
    defaultD = 5;
  }

  // Add bonuses to defaults
  Item *item = createItem(itemType, defaultH + h, defaultS + s, defaultD + d);

  if (item) {
    std::string itemKey = itemType + "_" + roomName;
    items[itemKey] = item;

    Room *room = rooms[roomName];
    if (room) {
      room->setItem(item);
    }
  }
}

void Game::placeMonster(const std::vector<std::string> &tokens) {
  if (tokens.size() < 7)
    return;

  std::string monsterName = tokens[2];
  std::string roomName = tokens[3];
  int h = std::stoi(tokens[4]);
  int s = std::stoi(tokens[5]);
  int d = std::stoi(tokens[6]);

  Monster *monster = new Monster(monsterName.c_str(), h, s, d);
  monsters[monsterName] = monster;

  Room *room = rooms[roomName];
  if (room) {
    room->setMonster(monster);
  }
}

void Game::enterDungeon(const std::vector<std::string> &tokens) {
  if (tokens.size() < 3)
    return;

  std::string charName = tokens[2];
  Character *character = characters[charName];
  Room *startRoom = dungeon->getStartRoom();

  if (character && startRoom) {
    currentCharacter = character;
    character->setCurrentRoom(startRoom);
    std::string output = charName + " enters the dungeon.";
    std::cout << output << std::endl;
    outputLines.push_back(output);
  }
}

void Game::moveCharacter(const std::vector<std::string> &tokens) {
  if (tokens.size() < 3 || !currentCharacter)
    return;

  std::string direction = tokens[2];
  Room *currentRoom = currentCharacter->getCurrentRoom();
  if (!currentRoom)
    return;

  Room *nextRoom = nullptr;
  if (direction == "North") {
    nextRoom = currentRoom->getNorth();
  } else if (direction == "South") {
    nextRoom = currentRoom->getSouth();
  } else if (direction == "East") {
    nextRoom = currentRoom->getEast();
  } else if (direction == "West") {
    nextRoom = currentRoom->getWest();
  }

  if (nextRoom) {
    currentCharacter->setCurrentRoom(nextRoom);
    std::string output = std::string(currentCharacter->getName()) + " moves " +
                         direction + " to " + nextRoom->getName() + ".";
    std::cout << output << std::endl;
    outputLines.push_back(output);
  } else {
    std::string output = "Cannot move " + direction + " (no connection).";
    std::cout << output << std::endl;
    outputLines.push_back(output);
  }
}

void Game::fightMonster(const std::vector<std::string> &tokens) {
  if (tokens.size() < 3 || !currentCharacter)
    return;

  std::string monsterName = tokens[2];
  Room *currentRoom = currentCharacter->getCurrentRoom();
  if (!currentRoom)
    return;

  Monster *monster = currentRoom->getMonster();
  if (!monster || strcmp(monster->getName(), monsterName.c_str()) != 0) {
    std::string output = std::string(currentCharacter->getName()) +
                         " tries to fight " + monsterName +
                         ": Failed (monster not in room).";
    std::cout << output << std::endl;
    outputLines.push_back(output);
    return;
  }

  // Turn-based combat: character attacks first
  while (currentCharacter->isAlive() && !monster->isDefeated()) {
    currentCharacter->attack(*monster);

    if (!monster->isDefeated()) {
      monster->attack(*currentCharacter);
    }
  }

  std::string output;
  if (monster->isDefeated()) {
    output = std::string(currentCharacter->getName()) + " fights " +
             monsterName + ": Victory";
    currentRoom->removeMonster();
  } else {
    output = std::string(currentCharacter->getName()) + " fights " +
             monsterName + ": Lose";
  }
  std::cout << output << std::endl;
  outputLines.push_back(output);
}

void Game::pickupItem(const std::vector<std::string> &tokens) {
  if (tokens.size() < 3 || !currentCharacter)
    return;

  std::string itemName = tokens[2];
  Room *currentRoom = currentCharacter->getCurrentRoom();
  if (!currentRoom)
    return;

  Item *item = currentRoom->getItem();
  if (!item) {
    std::string output = std::string(currentCharacter->getName()) +
                         " tries to pick up " + itemName +
                         ": Failed (no item in room).";
    std::cout << output << std::endl;
    outputLines.push_back(output);
    return;
  }

  if (strcmp(item->getName(), itemName.c_str()) != 0) {
    std::string output = std::string(currentCharacter->getName()) +
                         " tries to pick up " + itemName +
                         ": Failed (item not in room).";
    std::cout << output << std::endl;
    outputLines.push_back(output);
    return;
  }

  // Check equipment restrictions
  if (!currentCharacter->canEquip(*item)) {
    std::string output = std::string(currentCharacter->getName()) +
                         " tries to pick up " + itemName +
                         ": Failed (equipment restriction).";
    std::cout << output << std::endl;
    outputLines.push_back(output);
    return;
  }

  // Use operator+ to apply item effects
  Character updatedCharacter = *currentCharacter + *item;
  *currentCharacter = updatedCharacter;

  std::string output =
      std::string(currentCharacter->getName()) + " picks up " + itemName + ".";
  std::cout << output << std::endl;
  outputLines.push_back(output);

  // Remove item from room (unless it's a potion that was consumed)
  if (!item->isPotion()) {
    currentRoom->removeItem();
  } else {
    currentRoom->removeItem();
  }
}

void Game::printFinalStats() {
  if (!currentCharacter)
    return;

  std::cout << std::endl;
  outputLines.push_back(""); // Add blank line before final stats
  std::string output =
      std::string(currentCharacter->getName()) + "'s Final Stats:";
  std::cout << output << std::endl;
  outputLines.push_back(output);

  output = "Health: " + std::to_string(currentCharacter->getHealth());
  std::cout << output << std::endl;
  outputLines.push_back(output);

  output = "Strength: " + std::to_string(currentCharacter->getStrength());
  std::cout << output << std::endl;
  outputLines.push_back(output);

  output = "Defense: " + std::to_string(currentCharacter->getDefense());
  std::cout << output << std::endl;
  outputLines.push_back(output);

  output = "Inventory: " + currentCharacter->getInventoryString();
  std::cout << output << std::endl;
  outputLines.push_back(output);
}

void Game::loadFromFile(std::string filename) {
  std::ifstream inputFile(filename);
  if (!inputFile.is_open()) {
    std::cerr << "Error: Unable to open input file." << std::endl;
    return;
  }

  std::string line;
  while (getline(inputFile, line)) {
    parseAndExecute(line);
  }

  inputFile.close();
}

void Game::executeCommands() {
  // Commands are executed during loadFromFile
  // Print final stats after all commands
  printFinalStats();
}

void Game::outputFinalState(std::string filename) {
  std::ofstream outputFile(filename);
  if (!outputFile.is_open()) {
    std::cerr << "Error: Unable to open output file: " << filename << std::endl;
    return;
  }

  for (const std::string &line : outputLines) {
    outputFile << line << std::endl;
  }

  // Final stats are already in outputLines from printFinalStats()

  outputFile.flush(); // Ensure all data is written
  outputFile.close();

  if (outputFile.fail()) {
    std::cerr << "Error: Failed to write to output file: " << filename
              << std::endl;
  }
}
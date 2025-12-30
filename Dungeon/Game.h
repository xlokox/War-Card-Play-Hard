#pragma once
#include <iostream>
#include <map>
#include <string>
#include <vector>

class Character;
class Room;
class Item;
class Monster;
class Dungeon;

class Game {
private:
  Dungeon *dungeon;
  std::map<std::string, Character *> characters;
  std::map<std::string, Room *> rooms;
  std::map<std::string, Item *> items;
  std::map<std::string, Monster *> monsters;
  Character *currentCharacter;
  std::vector<std::string> outputLines;

  void parseAndExecute(const std::string &line);
  std::vector<std::string> splitString(const std::string &str);
  void createCharacter(const std::vector<std::string> &tokens);
  void createRoom(const std::vector<std::string> &tokens);
  void setStartRoom(const std::vector<std::string> &tokens);
  void connectRooms(const std::vector<std::string> &tokens);
  void placeItem(const std::vector<std::string> &tokens);
  void placeMonster(const std::vector<std::string> &tokens);
  void enterDungeon(const std::vector<std::string> &tokens);
  void moveCharacter(const std::vector<std::string> &tokens);
  void fightMonster(const std::vector<std::string> &tokens);
  void pickupItem(const std::vector<std::string> &tokens);

  Item *createItem(const std::string &type, int h, int s, int d);
  void printFinalStats();

public:
  Game();
  ~Game();

  void loadFromFile(std::string filename);
  void executeCommands();
  void outputFinalState(std::string filename);
};
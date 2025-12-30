#include "Monster.h"
#include "Item.h"
#include <string>

#pragma once

class Room; // Forward declaration

class Character {

protected:
    char *name;
    int health;
    int strength;
    int defense;
    Item **inventory;
    int inventorySize;
    int inventoryCapacity;
    Room *currentRoom;

public:
    Character(const char *n, int h, int s, int d);
    Character(const Character &other); // Copy constructor
    Character& operator=(const Character &other); // Assignment operator
    virtual ~Character();
    
    void attack(Monster &target);
    void defend(int damage);
    bool isAlive() const;
    int getDefense() const;
    int getHealth() const;
    int getStrength() const;
    const char* getName() const;
    
    Room* getCurrentRoom() const;
    void setCurrentRoom(Room* room);
    
    Character operator+(const Item &item);
    
    virtual bool canEquip(const Item &item) const;
    bool hasItemType(const char *typeName) const;
    Item* getItemByType(const char *typeName) const;
    void addToInventory(Item* item);
    void replaceItem(Item* oldItem, const Item* newItem);
    
    void printInventory() const;
    std::string getInventoryString() const;
};
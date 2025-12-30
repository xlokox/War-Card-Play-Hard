#include "Character.h"
#include "Room.h"
#include <cstring>
#include <cmath>
#include <iostream>
#include <string>
#include <algorithm>

Character::Character(const char *n, int h, int s, int d) 
    : health(h), strength(s), defense(d), inventorySize(0), inventoryCapacity(10), currentRoom(nullptr)
{
    this->name = new char[strlen(n) + 1];
    strcpy(this->name, n);
    this->inventory = new Item*[inventoryCapacity];
    for (int i = 0; i < inventoryCapacity; i++) {
        inventory[i] = nullptr;
    }
}

Character::Character(const Character &other)
    : health(other.health), strength(other.strength), defense(other.defense),
      inventorySize(other.inventorySize), inventoryCapacity(other.inventoryCapacity),
      currentRoom(other.currentRoom)
{
    this->name = new char[strlen(other.name) + 1];
    strcpy(this->name, other.name);
    this->inventory = new Item*[inventoryCapacity];
    for (int i = 0; i < inventorySize; i++) {
        inventory[i] = other.inventory[i]; // Just copy pointers, don't own items
    }
    for (int i = inventorySize; i < inventoryCapacity; i++) {
        inventory[i] = nullptr;
    }
}

Character& Character::operator=(const Character &other)
{
    if (this == &other) {
        return *this;
    }
    
    // Delete old data
    delete[] name;
    if (inventory) {
        delete[] inventory;
    }
    
    // Copy new data
    health = other.health;
    strength = other.strength;
    defense = other.defense;
    inventorySize = other.inventorySize;
    inventoryCapacity = other.inventoryCapacity;
    currentRoom = other.currentRoom;
    
    this->name = new char[strlen(other.name) + 1];
    strcpy(this->name, other.name);
    
    this->inventory = new Item*[inventoryCapacity];
    for (int i = 0; i < inventorySize; i++) {
        inventory[i] = other.inventory[i]; // Just copy pointers, don't own items
    }
    for (int i = inventorySize; i < inventoryCapacity; i++) {
        inventory[i] = nullptr;
    }
    
    return *this;
}

Character::~Character()
{
    delete[] name;
    if (inventory) {
        for (int i = 0; i < inventorySize; i++) {
            // Don't delete items here - they're owned by rooms or game
        }
        delete[] inventory;
    }
}

void Character::attack(Monster &target)
{
    int damage = static_cast<int>(std::max(1, this->strength - target.getDefense()));
    target.takeDamage(damage);
}

void Character::defend(int damage)
{
    // Damage is already calculated as max(1, attacker_strength - defender_defense)
    // So we just apply the damage directly
    this->health -= damage;
    if (this->health < 0) {
        this->health = 0;
    }
}

bool Character::isAlive() const
{
    return this->health > 0;
}

int Character::getDefense() const { return this->defense; }
int Character::getHealth() const { return this->health; }
int Character::getStrength() const { return this->strength; }
const char* Character::getName() const { return this->name; }

Room* Character::getCurrentRoom() const { return this->currentRoom; }
void Character::setCurrentRoom(Room* room) { this->currentRoom = room; }

bool Character::canEquip(const Item &item) const
{
    // Base class allows all items - subclasses will override
    // Potions can always be "equipped" (consumed) by any character
    (void)item; // Suppress unused parameter warning
    return true;
}

bool Character::hasItemType(const char *typeName) const
{
    for (int i = 0; i < inventorySize; i++) {
        if (inventory[i] && strcmp(inventory[i]->getName(), typeName) == 0) {
            return true;
        }
    }
    return false;
}

Item* Character::getItemByType(const char *typeName) const
{
    for (int i = 0; i < inventorySize; i++) {
        if (inventory[i] && strcmp(inventory[i]->getName(), typeName) == 0) {
            return inventory[i];
        }
    }
    return nullptr;
}

void Character::addToInventory(Item* item)
{
    if (inventorySize < inventoryCapacity) {
        inventory[inventorySize++] = item;
    }
}

void Character::replaceItem(Item* oldItem, const Item* newItem)
{
    for (int i = 0; i < inventorySize; i++) {
        if (inventory[i] == oldItem) {
            inventory[i] = const_cast<Item*>(newItem);
            break;
        }
    }
}

Character Character::operator+(const Item &item)
{
    Character result = *this;
    
    // Check equipment restrictions first
    if (!result.canEquip(item)) {
        return result;
    }
    
    // Check if it's a potion (consumed immediately, not stored)
    if (item.isPotion()) {
        result.health += item.getHealthBonus();
        result.strength += item.getStrengthBonus();
        result.defense += item.getDefenseBonus();
        return result;
    }
    
    // Check for duplicate equipment
    Item* existing = result.getItemByType(item.getName());
    if (existing) {
        int existingTotal = existing->getHealthBonus() + existing->getStrengthBonus() + existing->getDefenseBonus();
        int newTotal = item.getHealthBonus() + item.getStrengthBonus() + item.getDefenseBonus();
        
        if (newTotal > existingTotal) {
            // Remove old item stats
            result.health -= existing->getHealthBonus();
            result.strength -= existing->getStrengthBonus();
            result.defense -= existing->getDefenseBonus();
            
            // Add new item stats
            result.health += item.getHealthBonus();
            result.strength += item.getStrengthBonus();
            result.defense += item.getDefenseBonus();
            
            // Replace in inventory
            result.replaceItem(existing, &item);
        }
        // else: keep current item (totals equal or less)
    } else {
        // Add new equipment
        result.health += item.getHealthBonus();
        result.strength += item.getStrengthBonus();
        result.defense += item.getDefenseBonus();
        result.addToInventory(const_cast<Item*>(&item));
    }
    
    return result;
}

void Character::printInventory() const
{
    bool first = true;
    for (int i = 0; i < inventorySize; i++) {
        if (inventory[i]) {
            if (!first) std::cout << ", ";
            std::cout << inventory[i]->getName();
            first = false;
        }
    }
    if (first) {
        std::cout << "None";
    }
}

std::string Character::getInventoryString() const
{
    std::string result;
    bool first = true;
    for (int i = 0; i < inventorySize; i++) {
        if (inventory[i]) {
            if (!first) result += ", ";
            result += inventory[i]->getName();
            first = false;
        }
    }
    if (first) {
        result = "None";
    }
    return result;
}
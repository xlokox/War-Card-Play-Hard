#include "Room.h"
#include "Item.h"
#include "Monster.h"
#include <cstring>

Room::Room(const char *n) : north(nullptr), south(nullptr), east(nullptr), west(nullptr), item(nullptr), monster(nullptr)
{
    this->name = new char[strlen(n) + 1];
    strcpy(this->name, n);
}

Room::~Room()
{
    delete[] name;
    // Don't delete item or monster - they're owned by the game/dungeon
}

const char* Room::getName() const
{
    return this->name;
}

Room* Room::getNorth() const { return this->north; }
Room* Room::getSouth() const { return this->south; }
Room* Room::getEast() const { return this->east; }
Room* Room::getWest() const { return this->west; }

void Room::connectNorth(Room *room)
{
    this->north = room;
    if (room) {
        room->south = this;
    }
}

void Room::connectSouth(Room *room)
{
    this->south = room;
    if (room) {
        room->north = this;
    }
}

void Room::connectEast(Room *room)
{
    this->east = room;
    if (room) {
        room->west = this;
    }
}

void Room::connectWest(Room *room)
{
    this->west = room;
    if (room) {
        room->east = this;
    }
}

Item* Room::getItem() const { return this->item; }
Monster* Room::getMonster() const { return this->monster; }

void Room::setItem(Item *i) { this->item = i; }
void Room::setMonster(Monster *m) { this->monster = m; }

void Room::removeItem() { this->item = nullptr; }
void Room::removeMonster() { this->monster = nullptr; }


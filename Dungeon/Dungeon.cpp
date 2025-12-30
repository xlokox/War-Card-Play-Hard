#include "Dungeon.h"
#include "Room.h"
#include <cstring>

Dungeon::Dungeon() : startRoom(nullptr), roomCount(0), roomCapacity(20)
{
    rooms = new Room*[roomCapacity];
    for (int i = 0; i < roomCapacity; i++) {
        rooms[i] = nullptr;
    }
}

Dungeon::~Dungeon()
{
    if (rooms) {
        for (int i = 0; i < roomCount; i++) {
            delete rooms[i];
        }
        delete[] rooms;
    }
}

void Dungeon::setStartRoom(Room *room)
{
    this->startRoom = room;
}

Room* Dungeon::getStartRoom() const
{
    return this->startRoom;
}

void Dungeon::addRoom(Room *room)
{
    if (roomCount < roomCapacity) {
        rooms[roomCount++] = room;
    }
}

Room* Dungeon::findRoom(const char *name) const
{
    for (int i = 0; i < roomCount; i++) {
        if (rooms[i] && strcmp(rooms[i]->getName(), name) == 0) {
            return rooms[i];
        }
    }
    return nullptr;
}

int Dungeon::getRoomCount() const
{
    return roomCount;
}


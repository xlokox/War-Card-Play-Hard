#pragma once

class Room;

class Dungeon
{
private:
    Room *startRoom;
    Room **rooms;
    int roomCount;
    int roomCapacity;

public:
    Dungeon();
    ~Dungeon();
    
    void setStartRoom(Room *room);
    Room* getStartRoom() const;
    
    void addRoom(Room *room);
    Room* findRoom(const char *name) const;
    
    int getRoomCount() const;
};


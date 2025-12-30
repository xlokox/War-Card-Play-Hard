#pragma once

class Item;
class Monster;

class Room
{
private:
    char *name;
    Room *north;
    Room *south;
    Room *east;
    Room *west;
    Item *item;
    Monster *monster;

public:
    Room(const char *n);
    ~Room();
    
    const char* getName() const;
    
    Room* getNorth() const;
    Room* getSouth() const;
    Room* getEast() const;
    Room* getWest() const;
    
    void connectNorth(Room *room);
    void connectSouth(Room *room);
    void connectEast(Room *room);
    void connectWest(Room *room);
    
    Item* getItem() const;
    Monster* getMonster() const;
    
    void setItem(Item *i);
    void setMonster(Monster *m);
    
    void removeItem();
    void removeMonster();
};


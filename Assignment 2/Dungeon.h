class Dungeon {
private:
  Room *startRoom;

public:
  Dungeon();
  setStartRoom(Room *room);
  addRoom(Room *room);
  findRoom(char *name);
};
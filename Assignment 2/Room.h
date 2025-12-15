class Room
{
    private:
        char *name;
        Item item;
        Monster monster;

        public:
            Room north, south, east, west;

            //Methods
            setItem(Item *i);
            setMonster(Monster *m);
            connectNorth(Room *room);
            connectSouth(Room *room);
            connectEast(Room *room);
            connectWest(Room *room);
};
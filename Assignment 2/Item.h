#ifndef __ITEM_H
#define __ITEM_H

class Item {
private:
  char *name;
  int healthBonus;
  int strengthBonus;
  int defenseBonus;

public:
  Item(char *n, int h, int s, int d);
};

#endif
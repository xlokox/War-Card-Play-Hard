#ifndef __SWORD_H
#define __SWORD_H
#include "Item.h"

class Sword : public Item {
public:
  Sword(char *n, int h, int s, int d);
};

#endif
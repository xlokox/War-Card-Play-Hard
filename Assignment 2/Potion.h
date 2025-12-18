#ifndef __POTION_H
#define __POTION_H
#include "Item.h"

class Potion : public Item {
public:
  Potion(char *n, int h, int s, int d);
};

#endif
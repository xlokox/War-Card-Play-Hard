#ifndef __SHIELD_H
#define __SHIELD_H
#include "Item.h"

class Shield : public Item {
public:
  Shield(char *n, int h, int s, int d);
};

#endif
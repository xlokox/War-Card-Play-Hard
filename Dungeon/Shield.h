#include "Item.h"
#pragma once

class Shield : public Item
{
    public:
        Shield(const char *n="Shield", int h=0, int s=0, int d=5);
};

#include "Mage.h"
#include "Item.h"
#include <cstring>

Mage::Mage(const char *n) : Character(n, 40, 25, 5)
{
}

bool Mage::canEquip(const Item &item) const
{
    const char* itemName = item.getName();
    return (strcmp(itemName, "Wand") == 0);
}


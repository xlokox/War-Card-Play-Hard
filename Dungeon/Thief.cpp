#include "Thief.h"
#include "Item.h"
#include <cstring>

Thief::Thief(const char *n) : Character(n, 60, 20, 7)
{
}

bool Thief::canEquip(const Item &item) const
{
    const char* itemName = item.getName();
    return (strcmp(itemName, "Dagger") == 0);
}


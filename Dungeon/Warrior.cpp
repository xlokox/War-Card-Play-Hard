#include "Warrior.h"
#include "Item.h"
#include <cstring>

Warrior::Warrior(const char *n) : Character(n, 100, 15, 10)
{
}

bool Warrior::canEquip(const Item &item) const
{
    const char* itemName = item.getName();
    return (strcmp(itemName, "Sword") == 0 || strcmp(itemName, "Shield") == 0);
}


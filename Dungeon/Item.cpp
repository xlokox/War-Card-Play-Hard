#include "Item.h"
#include <cstring>

Item::Item(const char *n, int h, int s, int d) : healthBonus(h), strengthBonus(s), defenseBonus(d)
{
    this->name = new char[strlen(n) + 1];
    strcpy(this->name, n);
}

Item::~Item()
{
    delete[] this->name;
}

const char* Item::getName() const
{
    return this->name;
}

int Item::getHealthBonus() const
{
    return this->healthBonus;
}

int Item::getStrengthBonus() const
{
    return this->strengthBonus;
}

int Item::getDefenseBonus() const
{
    return this->defenseBonus;
}

bool Item::isPotion() const
{
    return false;
}
#include "Potion.h"
#include <cstring>

Potion::Potion(const char *n, int h, int s, int d) : Item(n,h,s,d)
{

}

void Potion::setHealthBonus(int val)
{
    this->healthBonus = val;
}

void Potion::setStrengthBonus(int val)
{
    this->strengthBonus = val;
}

void Potion::setDefenseBonus(int val)
{
    this->defenseBonus = val;
}

void Potion::setPotionName(const char *val)
{
    delete[] this->name;
    this->name = new char[strlen(val) + 1];
    strcpy(this->name, val);
}

bool Potion::isPotion() const
{
    return true;
}
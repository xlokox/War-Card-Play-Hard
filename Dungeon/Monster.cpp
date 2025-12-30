#include "Monster.h"
#include "Character.h"
#include <cstring>
#include <algorithm>

Monster::Monster(const char *n, int h, int s, int d) : health(h), strength(s), defense(d)
{
    this->name = new char[strlen(n) + 1];
    strcpy(this->name, n);
}

Monster::~Monster()
{
    delete[] name;
}

void Monster::attack(Character &target)
{
    int damage = static_cast<int>(std::max(1, this->strength - target.getDefense()));
    target.defend(damage);
}

void Monster::takeDamage(int damage)
{
    this->health -= damage;
    if (this->health < 0) {
        this->health = 0;
    }
}

bool Monster::isDefeated() const
{
   return this->health <= 0; 
}

const char* Monster::getName() const { return this->name; }
int Monster::getHealth() const { return this->health; }
int Monster::getStrength() const { return this->strength; }
int Monster::getDefense() const { return this->defense; }
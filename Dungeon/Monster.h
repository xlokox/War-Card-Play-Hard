#pragma once

class Character;

class Monster
{
private:
    char *name;
    int health;
    int strength;
    int defense;

public:
    Monster(const char *n, int h, int s, int d);
    ~Monster();
    
    void attack(Character &target);
    void takeDamage(int damage);
    bool isDefeated() const;

    const char* getName() const;
    int getHealth() const;
    int getStrength() const;
    int getDefense() const;
};
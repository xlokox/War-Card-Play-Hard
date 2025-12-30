
#pragma once

class Item
{
protected:
    char *name;
    int healthBonus;
    int strengthBonus;
    int defenseBonus;

public:
    Item(const char *n, int h, int s, int d);
    virtual ~Item();
    
    const char* getName() const;
    int getHealthBonus() const;
    int getStrengthBonus() const;
    int getDefenseBonus() const;
    
    virtual bool isPotion() const;
};
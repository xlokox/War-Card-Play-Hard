#include "Item.h"
#pragma once

class Potion : public Item
{//Potion kind being set at main program or by utility function from outside
    public:
        Potion(const char *n="Potion", int h=0, int s=0, int d=0);

        void setPotionName(const char *val);
        void setHealthBonus(int val);
        void setStrengthBonus(int val);
        void setDefenseBonus(int val);
        
        bool isPotion() const override;
};
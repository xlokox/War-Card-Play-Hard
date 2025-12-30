#include "Character.h"

#pragma once

class Mage : public Character
{
public:
    Mage(const char *n);
    bool canEquip(const Item &item) const override;
};


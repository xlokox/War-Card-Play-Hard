#include "Character.h"

#pragma once

class Thief : public Character
{
public:
    Thief(const char *n);
    bool canEquip(const Item &item) const override;
};


#include "Character.h"

#pragma once

class Warrior : public Character {
public:
  Warrior(const char *n);
  bool canEquip(const Item &item) const override;
};

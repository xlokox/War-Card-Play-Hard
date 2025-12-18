
class Character {
private:
  char *name;
  int health;
  int strength;
  int defense;

public:
  Character(char *n, int h, int s, int d);
  void attack(Monster &target);
  void defend(int damage);
  bool isAlive();
  Character operator+(const Item &item);
};
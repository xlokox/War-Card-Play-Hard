
//Monster will inherit from Character. Classes are not linked yet.
class Monster {
    private:
        char *name;
        int health;
        int strength;
        int defense;

        public:
            void attack(Character &target);
            bool isDefeated();
};
#ifndef STATS_H
#define STATS_H

#include <iostream>

struct Stats {
    int hp;
    int maxHp;
    int attack;
    int defense;
    int speed;
    int specialAttack;

    Stats()
        : hp(0), maxHp(0), attack(0), defense(0), speed(0), specialAttack(0) {}

    Stats(int hp, int attack, int defense, int speed, int specialAttack)
        : hp(hp), maxHp(hp), attack(attack), defense(defense),
          speed(speed), specialAttack(specialAttack) {}

    // Used for level-up stat boosts
    Stats operator+(const Stats& other) const {
        Stats result;
        result.maxHp = maxHp + other.maxHp;
        result.hp = hp + other.maxHp;  // heal by the maxHp boost amount
        result.attack = attack + other.attack;
        result.defense = defense + other.defense;
        result.speed = speed + other.speed;
        result.specialAttack = specialAttack + other.specialAttack;
        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const Stats& s) {
        os << "HP: " << s.hp << "/" << s.maxHp
           << " | ATK: " << s.attack
           << " | DEF: " << s.defense
           << " | SPD: " << s.speed
           << " | SP.ATK: " << s.specialAttack;
        return os;
    }
};

#endif // STATS_H

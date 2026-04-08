#ifndef POKEMON_H
#define POKEMON_H

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "Stats.h"
#include "Move.h"
#include "../types/Type.h"

class Pokemon {
private:
    std::string name;
    Type type;
    int level;
    Stats stats;
    std::vector<Move> moveset;
    int currentExp;
    int expToNext;

    void calculateExpToNext() {
        expToNext = level * level * 5;  // simple scaling formula
    }

public:
    Pokemon()
        : name("MissingNo"), type(Type::NORMAL), level(1),
          currentExp(0), expToNext(5) {}

    Pokemon(const std::string& name, Type type, int level, const Stats& baseStats,
            const std::vector<Move>& moves)
        : name(name), type(type), level(level), stats(baseStats),
          moveset(moves), currentExp(0) {
        calculateExpToNext();
    }

    // --- Getters ---
    const std::string& getName() const { return name; }
    Type getType() const { return type; }
    int getLevel() const { return level; }
    const Stats& getStats() const { return stats; }
    Stats& getMutableStats() { return stats; }
    const std::vector<Move>& getMoveset() const { return moveset; }
    int getCurrentExp() const { return currentExp; }
    int getExpToNext() const { return expToNext; }

    bool isAlive() const { return stats.hp > 0; }

    void takeDamage(int damage) {
        stats.hp = std::max(0, stats.hp - damage);
    }

    void heal(int amount) {
        stats.hp = std::min(stats.maxHp, stats.hp + amount);
    }

    void fullHeal() {
        stats.hp = stats.maxHp;
    }

    // Returns true if the Pokemon leveled up
    bool gainEXP(int amount) {
        currentExp += amount;
        if (currentExp >= expToNext) {
            levelUp();
            return true;
        }
        return false;
    }

    void levelUp() {
        level++;
        currentExp = 0;
        calculateExpToNext();

        // Stat boosts on level up
        Stats boost;
        boost.maxHp = 2 + (rand() % 3);       // +2 to +4
        boost.attack = 1 + (rand() % 2);       // +1 to +2
        boost.defense = 1 + (rand() % 2);
        boost.speed = 1 + (rand() % 2);
        boost.specialAttack = 1 + (rand() % 2);

        stats = stats + boost;
    }

    // HP bar string for display
    std::string getHPBar(int barLength = 20) const {
        int filled = 0;
        if (stats.maxHp > 0) {
            filled = (stats.hp * barLength) / stats.maxHp;
        }
        std::string bar = "[";
        for (int i = 0; i < barLength; i++) {
            bar += (i < filled) ? "|" : " ";
        }
        bar += "]";
        return bar;
    }

    friend std::ostream& operator<<(std::ostream& os, const Pokemon& p) {
        os << p.name << " [Lv." << p.level << " | " << typeToString(p.type) << "]"
           << "  HP: " << p.stats.hp << "/" << p.stats.maxHp
           << " " << p.getHPBar();
        return os;
    }
};

#endif // POKEMON_H

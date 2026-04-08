#ifndef MOVEFACTORY_H
#define MOVEFACTORY_H

#include "../entities/Move.h"
#include <string>
#include <unordered_map>
#include <functional>

class MoveFactory {
public:
    static Move create(const std::string& name) {
        static const std::unordered_map<std::string, Move> moveDB = {
            // Fire moves
            {"Ember",       Move("Ember",       Type::FIRE,     40, 100)},
            {"Flamethrower",Move("Flamethrower", Type::FIRE,    90, 100)},
            {"Fire Punch",  Move("Fire Punch",  Type::FIRE,     75,  95)},

            // Water moves
            {"Water Gun",   Move("Water Gun",   Type::WATER,    40, 100)},
            {"Bubble Beam", Move("Bubble Beam", Type::WATER,    65, 100)},
            {"Hydro Pump",  Move("Hydro Pump",  Type::WATER,   110,  80)},

            // Grass moves
            {"Vine Whip",   Move("Vine Whip",   Type::GRASS,   45, 100)},
            {"Razor Leaf",  Move("Razor Leaf",  Type::GRASS,    55,  95)},
            {"Solar Beam",  Move("Solar Beam",  Type::GRASS,   120, 100)},

            // Electric moves
            {"Thunder Shock", Move("Thunder Shock", Type::ELECTRIC, 40, 100)},
            {"Thunderbolt",   Move("Thunderbolt",   Type::ELECTRIC, 90, 100)},
            {"Spark",         Move("Spark",         Type::ELECTRIC, 65, 100)},

            // Normal moves
            {"Tackle",      Move("Tackle",      Type::NORMAL,   40, 100)},
            {"Scratch",     Move("Scratch",     Type::NORMAL,   40, 100)},
            {"Quick Attack",Move("Quick Attack",Type::NORMAL,   40, 100)},
            {"Pound",       Move("Pound",       Type::NORMAL,   40, 100)},
            {"Headbutt",    Move("Headbutt",    Type::NORMAL,   70, 100)},
            {"Body Slam",   Move("Body Slam",   Type::NORMAL,   85, 100)},
            {"Sing",        Move("Sing",        Type::NORMAL,    0,  55)},
        };

        auto it = moveDB.find(name);
        if (it != moveDB.end()) {
            return it->second;
        }
        // Fallback
        return Move("Struggle", Type::NORMAL, 30, 100);
    }
};

#endif // MOVEFACTORY_H

#ifndef POKEMONFACTORY_H
#define POKEMONFACTORY_H

#include "../entities/Pokemon.h"
#include "MoveFactory.h"
#include <string>
#include <vector>

class PokemonFactory {
public:
    // Creates a Pokemon by name at a given level, with scaled stats
    static Pokemon create(const std::string& name, int level) {
        // Base stats at level 1 — will be scaled by level
        if (name == "Charmander") {
            Stats base(39, 52, 43, 65, 60);
            scaleStats(base, level);
            return Pokemon(name, Type::FIRE, level, base, {
                MoveFactory::create("Scratch"),
                MoveFactory::create("Ember"),
                MoveFactory::create("Fire Punch")
            });
        }
        if (name == "Squirtle") {
            Stats base(44, 48, 65, 43, 50);
            scaleStats(base, level);
            return Pokemon(name, Type::WATER, level, base, {
                MoveFactory::create("Tackle"),
                MoveFactory::create("Water Gun"),
                MoveFactory::create("Bubble Beam")
            });
        }
        if (name == "Bulbasaur") {
            Stats base(45, 49, 49, 45, 65);
            scaleStats(base, level);
            return Pokemon(name, Type::GRASS, level, base, {
                MoveFactory::create("Tackle"),
                MoveFactory::create("Vine Whip"),
                MoveFactory::create("Razor Leaf")
            });
        }
        if (name == "Pikachu") {
            Stats base(35, 55, 40, 90, 50);
            scaleStats(base, level);
            return Pokemon(name, Type::ELECTRIC, level, base, {
                MoveFactory::create("Quick Attack"),
                MoveFactory::create("Thunder Shock"),
                MoveFactory::create("Thunderbolt")
            });
        }
        if (name == "Eevee") {
            Stats base(55, 55, 50, 55, 45);
            scaleStats(base, level);
            return Pokemon(name, Type::NORMAL, level, base, {
                MoveFactory::create("Tackle"),
                MoveFactory::create("Quick Attack"),
                MoveFactory::create("Headbutt")
            });
        }
        if (name == "Jigglypuff") {
            Stats base(115, 45, 20, 20, 45);
            scaleStats(base, level);
            return Pokemon(name, Type::NORMAL, level, base, {
                MoveFactory::create("Pound"),
                MoveFactory::create("Body Slam"),
                MoveFactory::create("Headbutt")
            });
        }

        // Fallback
        Stats base(40, 40, 40, 40, 40);
        scaleStats(base, level);
        return Pokemon("MissingNo", Type::NORMAL, level, base, {
            MoveFactory::create("Tackle")
        });
    }

    // Returns all available Pokemon names
    static std::vector<std::string> getRoster() {
        return { "Charmander", "Squirtle", "Bulbasaur", "Pikachu", "Eevee", "Jigglypuff" };
    }

private:
    // Scale base stats by level (simple linear scaling)
    static void scaleStats(Stats& base, int level) {
        float scale = 1.0f + (level - 1) * 0.08f;  // 8% per level
        base.hp = static_cast<int>(base.hp * scale);
        base.maxHp = base.hp;
        base.attack = static_cast<int>(base.attack * scale);
        base.defense = static_cast<int>(base.defense * scale);
        base.speed = static_cast<int>(base.speed * scale);
        base.specialAttack = static_cast<int>(base.specialAttack * scale);
    }
};

#endif // POKEMONFACTORY_H

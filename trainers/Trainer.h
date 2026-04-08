#ifndef TRAINER_H
#define TRAINER_H

#include <string>
#include <vector>
#include "../entities/Pokemon.h"

class Trainer {
protected:
    std::string name;
    std::vector<Pokemon> team;
    int activePokemonIndex;

public:
    Trainer() : name("Unknown"), activePokemonIndex(0) {}
    Trainer(const std::string& name) : name(name), activePokemonIndex(0) {}
    virtual ~Trainer() = default;

    const std::string& getName() const { return name; }

    void addPokemon(const Pokemon& pokemon) {
        team.push_back(pokemon);
    }

    Pokemon& getActivePokemon() {
        return team[activePokemonIndex];
    }

    const Pokemon& getActivePokemon() const {
        return team[activePokemonIndex];
    }

    std::vector<Pokemon>& getTeam() { return team; }
    const std::vector<Pokemon>& getTeam() const { return team; }

    int getActivePokemonIndex() const { return activePokemonIndex; }

    bool swapPokemon(int index) {
        if (index >= 0 && index < static_cast<int>(team.size())
            && index != activePokemonIndex
            && team[index].isAlive()) {
            activePokemonIndex = index;
            return true;
        }
        return false;
    }

    bool hasAlivePokemon() const {
        for (const auto& p : team) {
            if (p.isAlive()) return true;
        }
        return false;
    }

    // Selects the first alive Pokemon as active (used when current one faints)
    bool selectFirstAlive() {
        for (int i = 0; i < static_cast<int>(team.size()); i++) {
            if (team[i].isAlive()) {
                activePokemonIndex = i;
                return true;
            }
        }
        return false;
    }

    // Returns:
    //   >= 0  → move index chosen
    //   -1    → wants to swap (swap target stored via swapTarget param)
    virtual int chooseAction(const Pokemon& enemyActive, int& swapTarget) = 0;
};

#endif // TRAINER_H

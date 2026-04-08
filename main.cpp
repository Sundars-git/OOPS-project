// ============================================================
//   Pokemon Battle Game - C++ OOP Terminal Game
// ============================================================

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <limits>

#include "factory/PokemonFactory.h"
#include "trainers/HumanTrainer.h"
#include "trainers/AITrainer.h"
#include "strategy/AggressiveStrategy.h"
#include "battle/BattleEngine.h"

void printWelcome() {
    std::cout << "\n";
    std::cout << "==========================================\n";
    std::cout << "   \xf0\x9f\x8e\xae  POKEMON BATTLE SIMULATOR  \xf0\x9f\x8e\xae\n";
    std::cout << "==========================================\n";
    std::cout << "   A C++ OOP Turn-Based Battle Game\n";
    std::cout << "==========================================\n\n";
}

std::string getPlayerName() {
    std::string name;
    std::cout << "  Enter your trainer name: ";
    std::getline(std::cin, name);
    if (name.empty()) name = "Ash";
    return name;
}

std::vector<int> pickTeam(const std::vector<std::string>& roster, int teamSize) {
    std::cout << "\n  Choose " << teamSize << " Pokemon for your team:\n";
    std::cout << "  ----------------------------------------\n";
    for (int i = 0; i < static_cast<int>(roster.size()); i++) {
        Pokemon preview = PokemonFactory::create(roster[i], 10);
        std::cout << "    " << (i + 1) << ") " << preview << "\n";
        std::cout << "       " << preview.getStats() << "\n";
        std::cout << "       Moves: ";
        for (int j = 0; j < static_cast<int>(preview.getMoveset().size()); j++) {
            if (j > 0) std::cout << ", ";
            std::cout << preview.getMoveset()[j].name
                      << "(" << typeToString(preview.getMoveset()[j].type) << ")";
        }
        std::cout << "\n\n";
    }

    std::vector<int> chosen;
    while (static_cast<int>(chosen.size()) < teamSize) {
        std::cout << "  Pick Pokemon #" << (chosen.size() + 1) << ": ";
        int pick;
        if (!(std::cin >> pick)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "  Invalid input. Try again.\n";
            continue;
        }
        int idx = pick - 1;
        if (idx < 0 || idx >= static_cast<int>(roster.size())) {
            std::cout << "  Invalid choice. Pick 1-" << roster.size() << ".\n";
            continue;
        }
        if (std::find(chosen.begin(), chosen.end(), idx) != chosen.end()) {
            std::cout << "  Already picked! Choose a different one.\n";
            continue;
        }
        chosen.push_back(idx);
        std::cout << "  " << "\xe2\x9c\x93" << " " << roster[idx] << " added to your team!\n";
    }
    return chosen;
}

std::vector<int> pickRivalTeam(const std::vector<std::string>& roster,
                               const std::vector<int>& playerPicks, int teamSize) {
    std::vector<int> available;
    for (int i = 0; i < static_cast<int>(roster.size()); i++) {
        if (std::find(playerPicks.begin(), playerPicks.end(), i) == playerPicks.end()) {
            available.push_back(i);
        }
    }

    // Shuffle and pick
    for (int i = static_cast<int>(available.size()) - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        std::swap(available[i], available[j]);
    }

    std::vector<int> picks;
    for (int i = 0; i < teamSize && i < static_cast<int>(available.size()); i++) {
        picks.push_back(available[i]);
    }
    return picks;
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    printWelcome();

    // 1. Get player name
    std::string playerName = getPlayerName();

    // 2. Show roster and pick team
    std::vector<std::string> roster = PokemonFactory::getRoster();
    int pokemonLevel = 10;

    std::vector<int> playerPicks = pickTeam(roster, 3);

    // 3. Build player trainer
    HumanTrainer player(playerName);
    for (int idx : playerPicks) {
        player.addPokemon(PokemonFactory::create(roster[idx], pokemonLevel));
    }

    // 4. Build rival trainer with AggressiveStrategy
    std::vector<int> rivalPicks = pickRivalTeam(roster, playerPicks, 3);
    AITrainer rival("Gary", new AggressiveStrategy());
    for (int idx : rivalPicks) {
        rival.addPokemon(PokemonFactory::create(roster[idx], pokemonLevel));
    }

    std::cout << "\n  Your rival " << rival.getName() << " has chosen:\n";
    for (const auto& p : rival.getTeam()) {
        std::cout << "    " << "\xe2\x80\xa2" << " " << p.getName()
                  << " [Lv." << p.getLevel() << " | "
                  << typeToString(p.getType()) << "]\n";
    }
    std::cout << "\n  Get ready for battle!\n";
    std::cout << "  Press Enter to begin...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();

    // 5. Start battle!
    BattleEngine engine(&player, &rival);
    engine.startBattle();

    std::cout << "\n  Thanks for playing! Press Enter to exit...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();

    return 0;
}

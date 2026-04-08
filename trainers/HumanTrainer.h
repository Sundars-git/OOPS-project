#ifndef HUMANTRAINER_H
#define HUMANTRAINER_H

#include "Trainer.h"
#include <iostream>
#include <limits>

class HumanTrainer : public Trainer {
public:
    HumanTrainer() : Trainer() {}
    HumanTrainer(const std::string& name) : Trainer(name) {}

    int chooseAction(const Pokemon& enemyActive, int& swapTarget) override {
        (void)enemyActive; // not used by human — they read the screen

        Pokemon& active = getActivePokemon();
        const auto& moves = active.getMoveset();

        while (true) {
            std::cout << "\n  Your moves:\n";
            for (int i = 0; i < static_cast<int>(moves.size()); i++) {
                std::cout << "    " << (i + 1) << ") " << moves[i].name
                          << "  (" << typeToString(moves[i].type)
                          << " | Power: " << moves[i].power
                          << " | Acc: " << moves[i].accuracy << "%)\n";
            }
            std::cout << "    " << (moves.size() + 1) << ") SWAP POKEMON\n";
            std::cout << "  > ";

            int choice;
            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "  Invalid input. Try again.\n";
                continue;
            }

            // Move choice
            if (choice >= 1 && choice <= static_cast<int>(moves.size())) {
                return choice - 1;
            }

            // Swap choice
            if (choice == static_cast<int>(moves.size()) + 1) {
                int target = promptSwap();
                if (target >= 0) {
                    swapTarget = target;
                    return -1;
                }
                // If swap was cancelled, re-prompt
                continue;
            }

            std::cout << "  Invalid choice. Try again.\n";
        }
    }

private:
    int promptSwap() {
        std::cout << "\n  Choose a Pokemon to swap to:\n";
        bool hasOption = false;
        for (int i = 0; i < static_cast<int>(team.size()); i++) {
            if (i == activePokemonIndex) continue;
            if (!team[i].isAlive()) continue;
            hasOption = true;
            std::cout << "    " << (i + 1) << ") " << team[i] << "\n";
        }
        if (!hasOption) {
            std::cout << "  No other Pokemon available to swap!\n";
            return -1;
        }
        std::cout << "    0) Cancel\n";
        std::cout << "  > ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return -1;
        }

        if (choice == 0) return -1;

        int idx = choice - 1;
        if (idx >= 0 && idx < static_cast<int>(team.size())
            && idx != activePokemonIndex && team[idx].isAlive()) {
            return idx;
        }

        std::cout << "  Invalid swap target.\n";
        return -1;
    }
};

#endif // HUMANTRAINER_H

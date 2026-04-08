#ifndef BATTLELOGGER_H
#define BATTLELOGGER_H

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "../entities/Pokemon.h"
#include "../types/Type.h"

class BattleLogger {
public:
    static void printSeparator() {
        std::cout << "------------------------------------------\n";
    }

    static void printDoubleSeparator() {
        std::cout << "==========================================\n";
    }

    static void printBattleHeader(const std::string& player, const std::string& rival) {
        std::cout << "\n";
        printDoubleSeparator();
        std::cout << "       " << "\xe2\x9a\x94\xef\xb8\x8f" << "  POKEMON BATTLE  " << "\xe2\x9a\x94\xef\xb8\x8f" << "\n";
        printDoubleSeparator();
        std::cout << "  " << player << "  vs  " << rival << "\n";
        printDoubleSeparator();
        std::cout << "\n";
    }

    static void printSendOut(const std::string& trainer, const Pokemon& pokemon) {
        std::cout << "  " << trainer << " sent out " << pokemon.getName()
                  << "!  [Lv." << pokemon.getLevel() << " | "
                  << typeToString(pokemon.getType()) << "]\n\n";
    }

    static void printBattleStatus(const Pokemon& p1, const Pokemon& p2) {
        printSeparator();
        std::cout << "  " << p1 << "\n";
        std::cout << "  " << p2 << "\n";
        printSeparator();
    }

    static void printMoveUsed(const std::string& pokemonName, const std::string& moveName) {
        std::cout << "\n  " << pokemonName << " used " << moveName << "!\n";
    }

    static void printEffectiveness(float multiplier) {
        if (multiplier >= 2.0f) {
            std::cout << "  It's super effective! (2.0x)\n";
        } else if (multiplier <= 0.0f) {
            std::cout << "  It has no effect!\n";
        } else if (multiplier <= 0.5f) {
            std::cout << "  It's not very effective... (0.5x)\n";
        }
    }

    static void printCriticalHit() {
        std::cout << "  A critical hit!\n";
    }

    static void printDamage(const std::string& pokemonName, int damage) {
        std::cout << "  " << pokemonName << " took " << damage << " damage!\n";
    }

    static void printFainted(const std::string& pokemonName) {
        std::cout << "\n  " << pokemonName << " fainted!\n";
    }

    static void printSwap(const std::string& trainerName, const std::string& pokemonName) {
        std::cout << "\n  " << trainerName << " swapped to " << pokemonName << "!\n";
    }

    static void printExpGain(const std::string& pokemonName, int exp) {
        std::cout << "  " << pokemonName << " gained " << exp << " EXP!\n";
    }

    static void printLevelUp(const std::string& pokemonName, int newLevel) {
        std::cout << "  " << "\xf0\x9f\x8e\x89" << " " << pokemonName
                  << " grew to level " << newLevel << "!\n";
    }

    static void printVictory(const std::string& winnerName) {
        std::cout << "\n";
        printDoubleSeparator();
        std::cout << "  " << "\xf0\x9f\x8f\x86" << " " << winnerName << " wins the battle! " << "\xf0\x9f\x8f\x86" << "\n";
        printDoubleSeparator();
    }

    static void printDefeat(const std::string& loserName) {
        std::cout << "\n";
        printDoubleSeparator();
        std::cout << "  " << loserName << " has been defeated...\n";
        printDoubleSeparator();
    }

    static void printMissed(const std::string& pokemonName) {
        std::cout << "  " << pokemonName << "'s attack missed!\n";
    }

    static void pause(int ms = 1000) {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }
};

#endif // BATTLELOGGER_H

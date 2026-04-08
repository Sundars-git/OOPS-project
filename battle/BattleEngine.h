#ifndef BATTLEENGINE_H
#define BATTLEENGINE_H

#include "../trainers/Trainer.h"
#include "../types/TypeChart.h"
#include "BattleLogger.h"
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <string>

struct BattleStats {
    int totalDamageDealt = 0;
    int totalDamageReceived = 0;
    int knockouts = 0;
    int superEffectiveHits = 0;
    int criticalHits = 0;
    int totalExpGained = 0;
};

class BattleEngine {
private:
    Trainer* player;
    Trainer* rival;
    BattleStats playerStats;
    BattleStats rivalStats;

public:
    BattleEngine(Trainer* player, Trainer* rival)
        : player(player), rival(rival) {}

    void startBattle() {
        BattleLogger::printBattleHeader(player->getName(), rival->getName());

        BattleLogger::printSendOut(player->getName(), player->getActivePokemon());
        BattleLogger::printSendOut(rival->getName(), rival->getActivePokemon());

        // Main battle loop
        while (player->hasAlivePokemon() && rival->hasAlivePokemon()) {
            BattleLogger::printBattleStatus(
                player->getActivePokemon(),
                rival->getActivePokemon());

            executeTurn();

            // Check for faints and handle swaps
            handleFaints();

            if (!player->hasAlivePokemon() || !rival->hasAlivePokemon()) {
                break;
            }

            BattleLogger::pause(500);
        }

        // Determine winner
        if (player->hasAlivePokemon()) {
            BattleLogger::printVictory(player->getName());
        } else {
            BattleLogger::printDefeat(player->getName());
            BattleLogger::printVictory(rival->getName());
        }

        printPostBattleSummary();
    }

private:
    void executeTurn() {
        int playerSwapTarget = -1;
        int rivalSwapTarget = -1;

        int playerAction = player->chooseAction(rival->getActivePokemon(), playerSwapTarget);
        int rivalAction = rival->chooseAction(player->getActivePokemon(), rivalSwapTarget);

        // Handle swaps first (swaps happen before attacks)
        if (playerAction == -1 && playerSwapTarget >= 0) {
            player->swapPokemon(playerSwapTarget);
            BattleLogger::printSwap(player->getName(), player->getActivePokemon().getName());
        }
        if (rivalAction == -1 && rivalSwapTarget >= 0) {
            rival->swapPokemon(rivalSwapTarget);
            BattleLogger::printSwap(rival->getName(), rival->getActivePokemon().getName());
        }

        // If both swap, no attacks this turn
        if (playerAction == -1 && rivalAction == -1) return;

        Pokemon& playerPoke = player->getActivePokemon();
        Pokemon& rivalPoke = rival->getActivePokemon();

        // Determine attack order by speed
        bool playerFirst = playerPoke.getStats().speed >= rivalPoke.getStats().speed;

        if (playerAction >= 0 && rivalAction >= 0) {
            // Both attack
            if (playerFirst) {
                executeAttack(playerPoke, rivalPoke, playerAction, true);
                if (rivalPoke.isAlive()) {
                    executeAttack(rivalPoke, playerPoke, rivalAction, false);
                }
            } else {
                executeAttack(rivalPoke, playerPoke, rivalAction, false);
                if (playerPoke.isAlive()) {
                    executeAttack(playerPoke, rivalPoke, playerAction, true);
                }
            }
        } else if (playerAction >= 0) {
            // Only player attacks (rival swapped)
            executeAttack(playerPoke, rivalPoke, playerAction, true);
        } else if (rivalAction >= 0) {
            // Only rival attacks (player swapped)
            executeAttack(rivalPoke, playerPoke, rivalAction, false);
        }
    }

    void executeAttack(Pokemon& attacker, Pokemon& defender, int moveIndex, bool isPlayer) {
        const Move& move = attacker.getMoveset()[moveIndex];
        BattleLogger::printMoveUsed(attacker.getName(), move.name);
        BattleLogger::pause(600);

        // Accuracy check
        int accRoll = rand() % 100;
        if (accRoll >= move.accuracy) {
            BattleLogger::printMissed(attacker.getName());
            return;
        }

        float typeBonus;
        bool isCrit;
        int finalDamage = calculateDamage(attacker, defender, move, typeBonus, isCrit);

        // Log effectiveness
        BattleLogger::printEffectiveness(typeBonus);
        if (isCrit) {
            BattleLogger::printCriticalHit();
            if (isPlayer) playerStats.criticalHits++;
            else rivalStats.criticalHits++;
        }

        // Apply damage
        defender.takeDamage(finalDamage);
        BattleLogger::printDamage(defender.getName(), finalDamage);

        // Track stats
        if (isPlayer) {
            playerStats.totalDamageDealt += finalDamage;
            rivalStats.totalDamageReceived += finalDamage;
            if (typeBonus >= 2.0f) playerStats.superEffectiveHits++;
        } else {
            rivalStats.totalDamageDealt += finalDamage;
            playerStats.totalDamageReceived += finalDamage;
            if (typeBonus >= 2.0f) rivalStats.superEffectiveHits++;
        }

        BattleLogger::pause(400);
    }

    int calculateDamage(Pokemon& attacker, Pokemon& defender, const Move& move,
                        float& outTypeBonus, bool& outCrit) {
        float base = (2.0f * attacker.getLevel() / 5.0f + 2.0f)
                     * move.power
                     * attacker.getStats().attack
                     / static_cast<float>(defender.getStats().defense)
                     / 20.0f + 5.0f;

        outTypeBonus = TypeChart::getEffectiveness(move.type, defender.getType());
        outCrit = (rand() % 16 == 0);  // 1/16 crit chance
        float critical = outCrit ? 1.5f : 1.0f;
        float random = (85 + rand() % 16) / 100.0f;  // 85-100% variance

        float totalDamage = base * outTypeBonus * critical * random;
        return std::max(1, static_cast<int>(totalDamage));
    }

    void handleFaints() {
        // Check player's Pokemon
        if (!player->getActivePokemon().isAlive()) {
            BattleLogger::printFainted(player->getActivePokemon().getName());

            // Rival's active Pokemon gains EXP
            int expGain = calculateExpGain(player->getActivePokemon());
            rival->getActivePokemon().gainEXP(expGain);
            // (We don't display rival EXP gain to keep focus on player)

            if (player->hasAlivePokemon()) {
                std::cout << "\n  Choose your next Pokemon:\n";
                for (int i = 0; i < static_cast<int>(player->getTeam().size()); i++) {
                    if (player->getTeam()[i].isAlive()) {
                        std::cout << "    " << (i + 1) << ") " << player->getTeam()[i] << "\n";
                    }
                }
                std::cout << "  > ";
                int choice;
                while (true) {
                    if (!(std::cin >> choice)) {
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                        std::cout << "  Invalid. Try again: ";
                        continue;
                    }
                    int idx = choice - 1;
                    if (idx >= 0 && idx < static_cast<int>(player->getTeam().size())
                        && player->getTeam()[idx].isAlive()) {
                        player->swapPokemon(idx);
                        break;
                    }
                    std::cout << "  Invalid. Try again: ";
                }
                BattleLogger::printSendOut(player->getName(), player->getActivePokemon());
            }
        }

        // Check rival's Pokemon
        if (!rival->getActivePokemon().isAlive()) {
            BattleLogger::printFainted(rival->getActivePokemon().getName());

            // Player's active Pokemon gains EXP
            int expGain = calculateExpGain(rival->getActivePokemon());
            bool leveled = player->getActivePokemon().gainEXP(expGain);
            BattleLogger::printExpGain(player->getActivePokemon().getName(), expGain);
            playerStats.totalExpGained += expGain;
            if (leveled) {
                BattleLogger::printLevelUp(player->getActivePokemon().getName(),
                                           player->getActivePokemon().getLevel());
            }

            playerStats.knockouts++;

            if (rival->hasAlivePokemon()) {
                rival->selectFirstAlive();
                BattleLogger::printSendOut(rival->getName(), rival->getActivePokemon());
            }
        }
    }

    int calculateExpGain(const Pokemon& fainted) {
        // EXP = base(50) * faintedLevel / 5
        return 50 * fainted.getLevel() / 5;
    }

    void printPostBattleSummary() {
        std::cout << "\n";
        BattleLogger::printDoubleSeparator();
        std::cout << "         POST-BATTLE SUMMARY\n";
        BattleLogger::printDoubleSeparator();

        std::cout << "\n  " << player->getName() << "'s Stats:\n";
        BattleLogger::printSeparator();
        std::cout << "    Total Damage Dealt:     " << playerStats.totalDamageDealt << "\n";
        std::cout << "    Total Damage Received:  " << playerStats.totalDamageReceived << "\n";
        std::cout << "    Knockouts:              " << playerStats.knockouts << "\n";
        std::cout << "    Super Effective Hits:    " << playerStats.superEffectiveHits << "\n";
        std::cout << "    Critical Hits:           " << playerStats.criticalHits << "\n";
        std::cout << "    Total EXP Gained:        " << playerStats.totalExpGained << "\n";

        std::cout << "\n  Your Team After Battle:\n";
        BattleLogger::printSeparator();
        for (const auto& p : player->getTeam()) {
            std::cout << "    " << p << "\n";
        }

        std::cout << "\n";
        BattleLogger::printDoubleSeparator();
    }
};

#endif // BATTLEENGINE_H

#ifndef AGGRESSIVESTRATEGY_H
#define AGGRESSIVESTRATEGY_H

#include "AIStrategy.h"
#include "../types/TypeChart.h"

class AggressiveStrategy : public AIStrategy {
public:
    // Picks the move that deals the most estimated damage (power * type effectiveness)
    int chooseMove(const Pokemon& mine, const Pokemon& enemy) override {
        const auto& moves = mine.getMoveset();
        int bestIndex = 0;
        float bestScore = -1.0f;

        for (int i = 0; i < static_cast<int>(moves.size()); i++) {
            float effectiveness = TypeChart::getEffectiveness(moves[i].type, enemy.getType());
            float score = moves[i].power * effectiveness;
            if (score > bestScore) {
                bestScore = score;
                bestIndex = i;
            }
        }
        return bestIndex;
    }
};

#endif // AGGRESSIVESTRATEGY_H

#ifndef AITRAINER_H
#define AITRAINER_H

#include "Trainer.h"
#include "../strategy/AIStrategy.h"
#include <memory>

class AITrainer : public Trainer {
private:
    std::unique_ptr<AIStrategy> strategy;

public:
    AITrainer() : Trainer() {}
    AITrainer(const std::string& name, AIStrategy* strat)
        : Trainer(name), strategy(strat) {}

    int chooseAction(const Pokemon& enemyActive, int& swapTarget) override {
        (void)swapTarget;
        // AI always attacks — uses the strategy to pick the best move
        return strategy->chooseMove(getActivePokemon(), enemyActive);
    }
};

#endif // AITRAINER_H

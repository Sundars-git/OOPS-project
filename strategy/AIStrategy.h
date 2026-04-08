#ifndef AISTRATEGY_H
#define AISTRATEGY_H

#include "../entities/Pokemon.h"

class AIStrategy {
public:
    virtual ~AIStrategy() = default;
    // Returns the index of the move to use
    virtual int chooseMove(const Pokemon& mine, const Pokemon& enemy) = 0;
};

#endif // AISTRATEGY_H

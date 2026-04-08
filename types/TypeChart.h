#ifndef TYPECHART_H
#define TYPECHART_H

#include "Type.h"

class TypeChart {
public:
    // Returns the type effectiveness multiplier:
    //   2.0 = super effective
    //   1.0 = normal
    //   0.5 = not very effective
    //   0.0 = no effect
    static float getEffectiveness(Type attackType, Type defenseType) {
        // Indices map to: FIRE=0, WATER=1, GRASS=2, ELECTRIC=3, NORMAL=4
        //                       DEF:  FIRE  WATER  GRASS  ELEC  NORMAL
        static const float chart[5][5] = {
            /* ATK FIRE     */ { 0.5f, 0.5f,  2.0f,  1.0f, 1.0f },
            /* ATK WATER    */ { 2.0f, 0.5f,  0.5f,  1.0f, 1.0f },
            /* ATK GRASS    */ { 0.5f, 2.0f,  0.5f,  1.0f, 1.0f },
            /* ATK ELECTRIC */ { 1.0f, 2.0f,  0.5f,  0.5f, 1.0f },
            /* ATK NORMAL   */ { 1.0f, 1.0f,  1.0f,  1.0f, 1.0f }
        };

        int atkIdx = static_cast<int>(attackType);
        int defIdx = static_cast<int>(defenseType);

        if (atkIdx < 0 || atkIdx >= 5 || defIdx < 0 || defIdx >= 5)
            return 1.0f;

        return chart[atkIdx][defIdx];
    }
};

#endif // TYPECHART_H

#ifndef TYPE_H
#define TYPE_H

#include <string>

enum class Type {
    FIRE,
    WATER,
    GRASS,
    ELECTRIC,
    NORMAL,
    TYPE_COUNT  // sentinel for array sizing
};

inline std::string typeToString(Type t) {
    switch (t) {
        case Type::FIRE:     return "FIRE";
        case Type::WATER:    return "WATER";
        case Type::GRASS:    return "GRASS";
        case Type::ELECTRIC: return "ELECTRIC";
        case Type::NORMAL:   return "NORMAL";
        default:             return "UNKNOWN";
    }
}

#endif // TYPE_H

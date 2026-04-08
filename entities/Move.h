#ifndef MOVE_H
#define MOVE_H

#include <string>
#include "../types/Type.h"

struct Move {
    std::string name;
    Type type;
    int power;      // 0 = status move (not implemented, reserved)
    int accuracy;   // percentage 0-100

    Move() : name("Struggle"), type(Type::NORMAL), power(30), accuracy(100) {}

    Move(const std::string& name, Type type, int power, int accuracy)
        : name(name), type(type), power(power), accuracy(accuracy) {}
};

#endif // MOVE_H

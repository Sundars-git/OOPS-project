# 🎮 Pokemon Battle Simulator — C++ OOP Project

A **turn-based Pokemon battle game** built entirely in C++ to demonstrate core Object-Oriented Programming (OOP) concepts. Battle an AI rival trainer in the terminal with a team of 3 Pokemon, using type effectiveness, critical hits, and smart AI strategy.

---

## ✨ Features

- **Team-based 3v3 battles** — Pick 3 Pokemon from a roster of 6 and fight a rival AI trainer
- **Type effectiveness system** — Fire > Grass > Water > Fire, Electric > Water, etc.
- **Damage formula** — Inspired by the official Pokemon series with level scaling, attack/defense ratios, critical hits (1/16 chance), and damage variance (85–100%)
- **AI opponent** — Rival trainer uses an Aggressive Strategy to always pick the most effective move
- **EXP & Leveling** — Gain EXP from knockouts; Pokemon level up with randomized stat boosts
- **Pokemon swapping** — Swap your active Pokemon mid-battle for strategic advantage
- **Post-battle summary** — Detailed stats including total damage dealt, knockouts, critical hits, and EXP gained
- **Animated terminal UI** — HP bars, type labels, battle pauses, and formatted output

---

## 🏗️ OOP Concepts Demonstrated

| Concept | Where it's used |
|---|---|
| **Abstraction** | `AIStrategy` — pure virtual interface for AI behavior |
| **Inheritance** | `HumanTrainer` and `AITrainer` both inherit from `Trainer` |
| **Polymorphism** | `Trainer::chooseAction()` is a virtual method, allowing different behavior for human vs AI |
| **Encapsulation** | `Pokemon` class hides internal stats, exposing only getters and controlled methods like `takeDamage()` |
| **Composition** | `Pokemon` owns a `Stats` struct and a vector of `Move` objects |
| **Strategy Pattern** | `AITrainer` delegates move selection to an `AIStrategy` object (`AggressiveStrategy`) |
| **Factory Pattern** | `PokemonFactory` and `MoveFactory` centralize object creation |
| **Operator Overloading** | `Stats::operator+` for level-up boosts, `operator<<` for Pokemon/Stats display |

---

## 📁 Project Structure

```
OOPS-project/
├── main.cpp                    # Entry point — game loop, team selection, battle setup
├── CMakeLists.txt              # CMake build configuration
├── README.md                   # This file
│
├── entities/                   # Core data models
│   ├── Pokemon.h               # Pokemon class (HP, level, moves, EXP system)
│   ├── Stats.h                 # Stats struct (HP, ATK, DEF, SPD, SP.ATK)
│   └── Move.h                  # Move struct (name, type, power, accuracy)
│
├── types/                      # Type system
│   ├── Type.h                  # Type enum (FIRE, WATER, GRASS, ELECTRIC, NORMAL)
│   └── TypeChart.h             # 5×5 type effectiveness matrix
│
├── factory/                    # Object creation (Factory Pattern)
│   ├── PokemonFactory.h        # Creates Pokemon with scaled stats & movesets
│   └── MoveFactory.h           # Move database with 19 moves across 5 types
│
├── trainers/                   # Trainer hierarchy (Inheritance + Polymorphism)
│   ├── Trainer.h               # Abstract base class for all trainers
│   ├── HumanTrainer.h          # Player-controlled trainer (terminal input)
│   └── AITrainer.h             # AI-controlled trainer (uses Strategy Pattern)
│
├── strategy/                   # AI behavior (Strategy Pattern)
│   ├── AIStrategy.h            # Pure virtual strategy interface
│   └── AggressiveStrategy.h    # Picks highest-damage move considering type effectiveness
│
└── battle/                     # Battle system
    ├── BattleEngine.h          # Core battle loop, damage calculation, turn execution
    └── BattleLogger.h          # Formatted terminal output, HP bars, pauses
```

---

## 🚀 How to Build & Run

### Prerequisites
- A C++17 compatible compiler (g++, clang++, or MSVC)

### Option 1: Direct compilation (recommended)
```bash
g++ -o pokemon_battle main.cpp -std=c++17
./pokemon_battle
```

### Option 2: Using CMake
```bash
mkdir build && cd build
cmake ..
cmake --build .
./pokemon_battle
```

### On Windows (PowerShell)
```powershell
g++ -o pokemon_battle.exe main.cpp -std=c++17
.\pokemon_battle.exe
```

---

## 🎯 How to Play

1. **Enter your trainer name**
2. **Pick 3 Pokemon** from the roster of 6:
   - 🔥 Charmander (Fire) — Scratch, Ember, Fire Punch
   - 💧 Squirtle (Water) — Tackle, Water Gun, Bubble Beam
   - 🌿 Bulbasaur (Grass) — Tackle, Vine Whip, Razor Leaf
   - ⚡ Pikachu (Electric) — Quick Attack, Thunder Shock, Thunderbolt
   - 🐾 Eevee (Normal) — Tackle, Quick Attack, Headbutt
   - 🎤 Jigglypuff (Normal) — Pound, Body Slam, Headbutt
3. **Battle your rival** — Each turn, choose a move or swap Pokemon
4. **Win by knocking out all 3** of your rival's Pokemon!

---

## ⚔️ Type Effectiveness Chart

| Attack ↓ \ Defense → | Fire | Water | Grass | Electric | Normal |
|---|---|---|---|---|---|
| **Fire** | 0.5× | 0.5× | **2×** | 1× | 1× |
| **Water** | **2×** | 0.5× | 0.5× | 1× | 1× |
| **Grass** | 0.5× | **2×** | 0.5× | 1× | 1× |
| **Electric** | 1× | **2×** | 0.5× | 0.5× | 1× |
| **Normal** | 1× | 1× | 1× | 1× | 1× |

---

## 🧮 Damage Formula

```
Base = (2 × Level / 5 + 2) × MovePower × Attack / Defense / 20 + 5
Final = Base × TypeEffectiveness × CriticalHit × RandomVariance
```

- **Critical Hit**: 1/16 chance, deals 1.5× damage
- **Random Variance**: 85% to 100% of calculated damage
- **Accuracy**: Each move has an accuracy percentage; misses deal no damage

---

## 📜 License

This project is created for educational purposes to demonstrate C++ OOP concepts.

---

*Built with ❤️ and C++17*

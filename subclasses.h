#pragma once

#include "root.h"

namespace SubRole {

    struct StrengthBased : public RootRole::Player {
    protected:
        int strength;
    public:
        int attack() override {
            std::cout << name << " attacked with brute strength and dealt true damage equal to " << strength << " hp" << std::endl;
            return strength;
        }

        void defend(int damage) override {
            health -= damage * armor * 2  / 100;
        }
    }; // StrengthBased struct

    struct IntelligenceBased : public RootRole::Player {
    protected:
        int intelligence;
    public:
        int attack() {
            std::cout << name << " attacked with magic and dealt true equal to " << intelligence << " hp" << std::endl;
            return intelligence;
        }

        void defend(int damage) override {
            health -= damage * armor * 3  / 100;
        }
    }; // IntelligenceBased struct

    struct DexterityBased : public RootRole::Player {
    protected:
        int strength;
        int dexterity;
    public:
        int attack() {
            std::cout << name << " attacked swiftly and dealt true damage equal to " << strength / 2 + dexterity / 4 << " hp" << std::endl;
            return strength / 2 + dexterity / 4;
        }

        void defend(int damage) override {
            health -= damage * armor * (1 + dexterity / 50) / 100;
        }
    }; // DexterityBased struct

    struct FaithBased : public RootRole::Player {
    protected:
        int strength;
        int faith;
    public:
        int attack() {
            std::cout << name << " attacked in a name of god and dealt true damage equal to " << strength / 2 + faith / 2 << " hp" << std::endl;
            return strength / 2 + faith / 2;
        }

        void defend(int damage) override {
            health -= damage * armor * 1.8  / 100;
        }
    }; // FaithBased struct

    struct Summoner : public RootRole::Player {
    protected:
        int intelligence;
        int summons;
        int cumulative_attack;
    public:
        int attack() {
            std::cout << name << " has struck the enemy with their summoning wands dealing " << intelligence * 3/4 << std::endl;
            return intelligence * 3/4;
        }

        void defend(int damage) override {
            health -= damage * armor * 3  / 100;
        }
    }; // Summoner struct

}; // SubRole namespace
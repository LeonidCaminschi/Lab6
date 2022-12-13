#pragma once

#include <iostream>

#include "subclasses.h"

using namespace std;

namespace Roles {

    struct Marauder : public SubRole::StrengthBased { // 1st class
    private:
        bool buffed;
    public:
        Marauder() :
            SubRole::StrengthBased()
        {
            name = "Marauder";
            max_health = 35;
            armor = 20;
            max_mana = 12;
            strength = 22;
            luck = 13;
            health = max_health;
            mana = max_mana;
            buffed = false;
        }

        void rage() {
            if (!buffed) {
                strength += 5;
                health -= 5;
                mana -= 3;
                if(!check_alive()) return;
                cout << name << " used rage gained strength and lost a bit of hp and mana" << endl;
            }
        }

        template <class T> // TODO: not all classes have strength
        void fear(T& enemy) {
            if (strength > enemy.strength) {
                enemy.strength -= 5;
                cout << "Marauder feared the enemy reducing his strength" << endl;
            } else {
                cout << "Marauder's fear failed due to enemy being stronger than him" << endl;
            }
        }

        int dual_chop() {
            if (mana >= 9) {
                std::cout << name << " dual chopped the enemy and dealt damage equal to " << strength * 3 / 4 * 2
                          << " hp" << std::endl;
                mana -= 9;
                return strength * 3 / 4 * 2;
            } else {
                std::cout << name << " failed to use dual chop due to lack of mana" << endl;
                return 0;
            }
        }

        int pseudo_ai() {
            if (!buffed) {
                rage();
                return 0;
            }

            if (mana >= 9)
                return dual_chop();
            else
                meditate();

            return 0;
        }
    };

    struct Wizard : public SubRole::IntelligenceBased { // 2nd class
    private:
        bool buffed;
    public:
        Wizard() {
            name = "Wizard";
            max_health = 20;
            armor = 12;
            max_mana = 32;
            intelligence = 26;
            luck = 14;
            alive = true;
            health = max_health;
            mana = max_mana;
            buffed = false;
        }

        void reflection() {
            if (!buffed) {
                if (mana >= 8) {
                    armor += 10;
                    mana -= 8;
                    buffed = true;
                    cout << name << " used reflection raising his armor" << endl;
                } else {
                    cout << name << " failed to use reflection due to lack of mana" << endl;
                }
            }
        }

        template <class T>
        int arcane_trap(T& enemy) {
            if (mana >= 12) {
                cout << name << " used arcane trap shredding their armor and dealing a bit of true damage equal to 5 hp" << endl;
                enemy.armor -= (enemy.armor - 3 < 0) ? enemy.armor : 3;
                mana -= 12;
                return 5;
            } else {
                cout << name << " failed to use arcane trap due to lack of mana" << endl;
                return 0;
            }
        }

        int thunderStrike() {
            if (mana >= 15) {
                std::cout << name << " used thunder strike the enemy and dealt true damage equal to "
                          << intelligence * 3 / 2 << " hp" << std::endl;
                mana -= 15;
                return intelligence * 3 / 2;
            } else {
                cout << name << " failed to use thunder strike due to lack of mana" << endl;
                return 0;
            }
        }

        int pseudo_ai() {
            if (!buffed) {
                reflection();
                return 0;
            }

            if (mana >= 15)
                return thunderStrike();
            else
                meditate();

            return 0;
        }
    };

    struct Rogue : SubRole::DexterityBased{ // 3rd class
    private:
        bool buffed;
    public:
        Rogue() {
            name = "Rogue";
            max_health = 15;
            armor = 9;
            max_mana = 24;
            strength = 18;
            dexterity = 31;
            luck = 21;
            alive = true;
            health = max_health;
            mana = max_mana;
            buffed = false;

        }

        void intoTheShadows() {
            if (!buffed) {
                if (mana >= 7) {
                    dexterity += 10;
                    mana -= 7;
                    buffed = true;
                    cout << name << " covered himself with darkness to hide" << endl;
                } else {
                    cout << name << " failed to cover himself darkness due to lack of mana" << endl;
                }
            }
        }

        void smokeScreen(int &enemy_accuracy) {
            enemy_accuracy /= 3;
        }

        int poisonStrike() {
            if (mana >= 12) {
                cout << name << " used poison strike and dealt true damage equal to " << dexterity + strength * 2 << endl;
                return dexterity + strength * 2;
            } else {
                cout << name << " failed to use poison strike due to lack of mana" << endl;
                return 0;
            }
        }

        int pseudo_ai() {
            if (!buffed) {
                intoTheShadows();
                return 0;
            }

            if (mana >= 12)
                return poisonStrike();
            else
                meditate();

            return 0;
        }
    };

    struct Crusader : public SubRole::FaithBased { // 4th class
    public:
        Crusader() {
            name = "Crusader";
            max_health = 40;
            armor = 18;
            max_mana = 12;
            luck = 8;
            alive = true;
            faith = 18;
            strength = 18;
            health = max_health;
            mana = max_mana;
        }

        void holy_heal() {
            if (mana >= 12) {
                if (health + faith > max_health) {
                    health = max_health;
                } else {
                    health += faith;
                }
                mana -= 12;
                cout << name << " has been healed by the holy force current hp " << health << endl;
            } else {
                cout << name << " has faile to heal due to lack of mana " << endl;
            }
        }

        int armorBash() {
            cout << name << " jumped on the enemy in his heavy armor dealing " << armor << " true damage" << endl;
            return armor;
        }

        int lastBreathe() {
            cout << name << " used the remaining of his life to launch a huge attack dying in the process" << endl;
            health = 0;
            alive = false;
            return faith * 5/4;
        }

        int pseudo_ai() {
            if (health <= max_health - faith) {
                if (mana == 12) {
                    holy_heal();
                    return 0;
                } else {
                    if (health <= max_health * 1/8)
                        return lastBreathe();
                    meditate();
                    return 0;
                }
            }

            return armorBash();
        }
    };

    struct Highwayman : SubRole::DexterityBased { // 5th class
    public:
        Highwayman() {
            name = "Highwayman";
            max_health = 20;
            armor = 10;
            max_mana = 9;
            strength = 23;
            luck = 18;
            alive = true;
            health = max_health;
            mana = max_mana;
        }

        int shoot() {
            if (mana >= 3) {
                mana -= 3;
                cout << name << " shoot the enemy dealing damage equal to " << (3 / 2 * strength) << endl;
                return (3 / 2 * strength);
            } else {
                cout << name << " was unable to shoot due to lack of mana and bullets " << endl;
                return 0;
            }
        }

        int ignite() {
            if (mana >= 1) {
                mana -= 1;
                cout << name << " ignited a barrel with poweder dealing flat " << 15 << " points of damage" << endl;
                return 15;
            } else {
                cout << name << " could not ignite the barrel due to lack of mana and matches" << endl;
                return 0;
            }
        }

        void eatOrange() {
            if (mana >= 9) {
                health = max_health;
                max_health -= 1;
                mana -= 9;
                cout << name << " ate an orange healing to full hp but decreasing max hp" << endl;
            } else {
                cout << name << " could not heal to full hp due to lack of mana and oranges" << endl;
            }
        }

        int pseudo_ai() {
            if (health < 1/4) {
                if (mana >= 9) {
                    eatOrange();
                    return 0;
                } else {
                    meditate();
                    return 0;
                }
            }

            if(mana >= 3) return shoot();
            if(mana >= 1) return ignite();
            meditate();
            return 0;
        }
    };

    struct Abomination : SubRole::FaithBased { // 6th class
    private:
        bool beast;
    public:
        Abomination() {
            name = "Abomination";
            max_health = 32;
            armor = 17;
            max_mana = 2;
            strength = 25;
            luck = 14;
            alive = true;
            beast = false;
            faith = 2;
            health = max_health;
            mana = max_mana;
        }

        int lunge() {
            if (mana >= 3) {
                mana -= 3;
                cout << name << " dealt lunged at the enemy dealing true damage equal to " << 3 / 2 * strength << endl;
                return 3 / 2 * strength;
            } else {
                cout << name << " failed to lunge due to lack of mana" << endl;
                return 0;
            }
        }

        void beastTransform() {
            if (!beast) {
                strength *= 2;
                health /= 2;
                max_health /= 2;
                beast = true;
                cout << name << " turned into a beast greatly incesing strength but greatly decreasing health" << endl;
            } else {
                cout << name << " could not turn into a beast due to already being one" << endl;
            }
        }

        int bite() {
            if (beast) {
                if (mana >= 1) {
                    cout << name << " bit his opponent while in beast form dealing " << strength*2 << " true damage" << endl;
                    return strength*2;
                } else {
                    cout << name << " could not bite the enemy due to lack of mana " << endl;
                    return 0;
                }
            } else {
                cout << name << " could not bit the enemy due to him not being in beast form" << endl;
                return 0;
            }
        }

        int pseudo_ai() {
            if(!beast) {
                beastTransform();
                return 0;
            }

            if(mana >= 1) return bite();
            meditate();
            return 0;
        }
    };

    struct Knight : SubRole::StrengthBased { // 7th class
    private:
        bool buffed;
    public:
        Knight() {
            name = "Knight";
            max_health = 42;
            armor = 21;
            max_mana = 0;
            strength = 21;
            luck = 11;
            alive = true;
            health = max_health;
            mana = max_mana;
            buffed = false;
        }

        int lunge() {
            cout << name << " by the sheer power he lunges at the enemy dealing " << 3 / 2 * strength << " damage" << endl;
            return 3 / 2 * strength;
        }

        void fortify() {
            if (!buffed) {
                armor += 1 / 4 * armor;
                cout << name << " inceased his armor" << endl;
                buffed = true;
            } else {
                cout << name << " couldn't increase his armor any more" << endl;
            }
        }

        int shield_bash() {
            cout << name << " shield bashed the enemy to deal " << 1 / 2 * strength << endl;
            return 1 / 2 * strength;
        }

        int pseudo_ai() {
            if(!buffed) {
                fortify();
                return 0;
            }

            return lunge();
        }
    };

    struct Necromancer : SubRole::Summoner { // 8th class
    private:
        bool buffed;
    public:
        Necromancer() {
            name = "Necromancer";
            max_health = 31;
            armor = 12;
            max_mana = 20;
            intelligence = 19;
            luck = 13;
            alive = true;
            health = max_health;
            mana = max_mana;
            buffed = false;
            summons = 0;
            cumulative_attack = 0;
        }

        int steal() {
            if (mana >= 3) {
                mana -= 3;
                health += 1 / 6 * intelligence;
                cout << name << " stolen the lifeforce of the enemy dealing " << 1 / 2 * intelligence << " damage and healing "
                << 1 / 6 * intelligence << endl;
                return 1 / 2 * intelligence;
            } else {
                cout << name << " could not draim the lifeforce of the enemy due to lack of mana" << endl;
                return 0;
            }
        }

        void undead_armor() {
            if (!buffed) {
                if (mana >= 8) {
                    armor += 1 / 2 * armor;
                    mana -= 8;
                    cout << name << " has applied the corpses of fallen heroes to his armor" << endl;
                } else {
                    cout << name << " has failed to increase armor due lack of mana" << endl;
                }
            } else {
                cout << name << " has failed to increase armor due to him already doing it" << endl;
            }
        }

        int summonUndead() {
            if (mana >= 15) {
                if (summons < 3) {
                    mana -= 15;
                    cumulative_attack += 7;
                    summons++;
                    cout << name << " has summoned an extra zombie to the battle" << endl;
                } else {
                    cout << name << " could not summon the enemy due to lack of battlefield space" << endl;
                }
            } else {
                cout << name << " could not summon the enemy due to lack of battlefield space" << endl;
            }
            return cumulative_attack;
        }

        int pseudo_ai() {
            if(!buffed) {
                undead_armor();
                return 0;
            }

            if (health <= 1/3 * max_health || summons == 3) {
                if (mana >= 3)
                    return steal();
                else {
                    meditate();
                    return 0;
                }
            }

            if (summons < 3) {
                if (mana >= 15)
                    return summonUndead();
                else {
                    meditate();
                    return 0;
                }
            }
        }
    };

    struct Priest : SubRole::FaithBased { // 9th class
    public:
        Priest() {
            name = "Priest";
            max_health = 28;
            armor = 8;
            max_mana = 25;
            strength = 6;
            luck = 12;
            alive = true;
            faith = 21;
            health = max_health;
            mana = max_mana;
        }

        int holyFire() {
            if (mana >= 5) {
                mana -= 5;
                armor++;
                cout << name << " has casted holy fire on the enemies dealing " << 1 / 2 * faith << " damage" << endl;
                return 1 / 2 * faith;
            } else {
                cout << name << "could not cast holy fire due to lack of mana" << endl;
                return 0;
            }
        }

        void holyHeal() {
            if (mana >= 10) {
                if (health + 3/4 * faith > max_health) {
                    health = max_health;
                } else {
                    health += faith;
                }
                mana -= 10;
                cout << name << " has been healed by the holy force current hp " << health << endl;
            } else {
                cout << name << " has failed to heal due to lack of mana " << endl;
            }
        }

        template <class T>
        void revive(T& ally) { //TODO cant revive 1 on 1
            if (mana >= 25) {
                if (ally.health <= 0) {
                    alive = true;
                    ally.health = 1;
                    mana -= 25;
                    cout << name << " revived " << ally.name << " by the power of Gods" << endl;
                } else {
                    cout << name << " could not revive " << ally.name << " because they are still alive" << endl;
                }
            } else {
                cout << name << " could not cast revive due to lack of mana" << endl;
            }
        }

        int pseudo_ai() {
            if (health <= max_health - 3/4 * faith) {
                if (mana >= 10) {
                    holyHeal();
                    return 0;
                } else {
                    meditate();
                    return 0;
                }
            }

            if (mana >= 5) {
                return holyFire();
            } else {
                meditate();
                return 0;
            }
        }
    };

    struct Summoner : SubRole::Summoner { // 8th class
    public:
        Summoner() {
            name = "Summoner";
            max_health = 24;
            armor = 11;
            max_mana = 31;
            intelligence = 23;
            luck = 9;
            alive = true;
            summons = 0;
            cumulative_attack = 0;
            health = max_health;
            mana = max_mana;
        }

        int summonDamage() {
            if (mana >= 7) {
                mana -= 7;
                cout << name << " has ordered his summons to attack" << endl;
                return cumulative_attack;
            } else {
                cout << name << " has failed to order his summons to attack" << endl;
            }
        }

        int summonSpirit() {
            if (summons < 3) {
                if (mana >= 3) {
                    summons++;
                    mana -= 3;
                    cumulative_attack += 1 / 4 * intelligence;
                    cout << name << " has summoned a spirit on the battlefield" << endl;
                } else {
                    cout << name << " could not summon spirit due to lack of mana" << endl;
                }
            } else {
                cout << name << " could not summon spirit due to lack of battlefield space" << endl;
            }
            return cumulative_attack;
        }

        int summonGuardian() {
            if (summons < 3) {
                if (mana >= 15) {
                    summons += 2;
                    mana -= 15;
                    cumulative_attack += 2 / 4 * intelligence;
                    cout << name << " has summoned a golem on the battlefield thus increasing his defence" << endl;
                } else {
                    cout << name << " could not summon golem due to lack of mana" << endl;
                }
            } else {
                cout << name << " could not summon golem due to lack of battlefield space" << endl;
            }
            return cumulative_attack;
        }

        int summonBear() {
            if (summons < 2) {
                if (mana >= 10) {
                    summons += 2;
                    mana -= 10;
                    cumulative_attack += 3 / 4 * intelligence;
                    cout << name << " has summoned a bear on the battlefield thus increasing his defence" << endl;
                } else {
                    cout << name << " could not summon spirit due to lack of mana" << endl;
                }
            } else {
                cout << name << " could not summon spirit due to lack of battlefield space" << endl;
            }
            return cumulative_attack;
        }

        int pseudo_ai() {
            if (summons < 2) {
                if (mana >= 15) {
                    return summonGuardian();
                } else {
                    meditate();
                    return 0;
                }
            }

            if (summons < 3) {
                if(mana >= 3) {
                    return summonSpirit();
                } else {
                    meditate();
                    return 0;
                }
            }

            if (summons == 3) {
                if (mana >= 7) {
                    return summonDamage();
                } else {
                    meditate();
                    return 0;
                }
            }
        }
    };
} // namespace Roles

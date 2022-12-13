#include "classes.h"
#include "army.h"
#include <random>

using namespace std;

#pragma once

struct Battlefield {
private:
    char** field;
    int maxSize = 13;
    manager armies;

    void initField() {
        field = new char*[maxSize];
        for (int i=0; i<maxSize; i++) {
            field[i] = new char[maxSize];
            for (int j=0; j<maxSize; j++) {
                field[i][j] = ' ';
            }
        }
    }

    void randomizeFighters(int* nr, int x, int y) {
        int role = rand() % 10;
        while (nr[role] >= 2) {
            role = rand() % 10;
        }
        switch (role) {
            case 0:
                armies.armies.push_back(army(new Roles::Marauder(), "Marauder", x, y));
                break;
            case 1:
                armies.armies.push_back(army(new Roles::Wizard(), "Wizard", x, y));
                break;
            case 2:
                armies.armies.push_back(army(new Roles::Rogue(), "Rogue", x, y));
                break;
            case 3:
                armies.armies.push_back(army(new Roles::Crusader(), "Crusader", x, y));
                break;
            case 4:
                armies.armies.push_back(army(new Roles::Highwayman(), "Highwayman", x, y));
                break;
            case 5:
                armies.armies.push_back(army(new Roles::Abomination(), "Abomination", x, y));
                break;
            case 6:
                armies.armies.push_back(army(new Roles::Knight(), "Knight", x, y));
                break;
            case 7:
                armies.armies.push_back(army(new Roles::Necromancer(), "Necromancer", x, y));
                break;
            case 8:
                armies.armies.push_back(army(new Roles::Priest(), "Priest", x, y));
                break;
            case 9:
                armies.armies.push_back(army(new Roles::Summoner(), "Summoner", x, y));
                break;
        }
        nr[role]++;
    }

    void placeFighters() {
        int nr[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        int pos[] = {1, 3, 5, 7, 9, 11};
        srand(time(0));
        for (int i=0; i<6; i++) {
            for (int j=0; j<6; j++) {
                if ((i == 0 || i == 5) || (j == 0 || j == 5)) {
                    randomizeFighters(nr, pos[i], pos[j]);
                }
            }
        }
    }

    void displayBattlefield() {
        for (int i=0; i<maxSize-1; i++) {
            for (int j=0; j<maxSize-1; j++) {
                cout << field[i][j] << " ";
            }
            cout << endl;
        }
    }

    void refreshBattlefield() {
        for (auto army : armies.armies) {
            field[army.x][army.y] = army.name[0];
        }
        displayBattlefield();
    }

    char scanCell(int x, int y) {
        if (x < 0 || x > 12 || y < 0 || x > 12)
            return ' ';
        return field[x][y];
    }

    void checkSurundings(army& army) {
        int signal = 0;
        for (int x=-1; x<=1; x++) {
            for (int y=-1; y<=1; y++) {
                if (x == 0 && y == 0) continue;
                signal = army.scanArea(scanCell(army.x + x, army.y + y));

                if (signal == 2) {
                    army.unit->combine_forces(armies.find(army.x + x, army.y + y));
                    armies.kill(army.x + x, army.y + y);
                    field[army.x+x][army.y+y] = ' ';
                }

                if (signal == 3)  {
                    auto enemy = armies.find(army.x + x, army.y + y);
                    while (army.unit->check_alive() && enemy->check_alive()) {
                        enemy->defend(army.unit->pseudo_ai());
                        if (!enemy->check_alive()) break;
                        army.unit->defend(enemy->pseudo_ai());
                    }
                    if (!enemy->check_alive()) {
                        field[army.x+x][army.y+y] = ' ';
                        armies.kill(army.x + x, army.y + y);
                    } else {
                        field[army.x][army.y] = ' ';
                        armies.kill(army.x, army.y);
                        break;
                    }
                }
            }
        }
    }

    void removeOld(int x, int y) {
        field[x][y] = ' ';
    }

public:
    Battlefield() {
        initField();
        placeFighters();
        // Events
        refreshBattlefield();
    }

    void startBattle() {
        while(armies.armies.size() > 1) {
            for (auto& army : armies.armies) {
                checkSurundings(army);
                pair<int, int> coord = army.move();
                removeOld(coord.first, coord.second);
                checkSurundings(army);
                refreshBattlefield();
            }
//            break;
        }
    }

    ~Battlefield() {
        for (int i=0; i<10; i++) {
            delete(field[i]);
        }
        delete(field);
    }
};
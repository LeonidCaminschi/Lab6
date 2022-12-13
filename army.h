#include "classes.h"
#include <vector>

#pragma once

struct army {
    RootRole::Player *unit;
    string name;
    int x;
    int y;

    army(void* role, string rname, int& posx, int& posy) {
        unit = reinterpret_cast<RootRole::Player*>(role);
        name = rname;
        x = posx;
        y = posy;
    }

    int scanArea(char cell)  {
        if (cell == ' ') {
            return 0;
        }

        if (cell == 'E') {
            // event
            return 1;
        }

        if (cell == name[0]) {
            // ally
            return 2;
        }

        if (cell != 'E' && cell != name[0]) {
            return 3;
        }
    }

    pair<int, int> move() {
        int oldx = x;
        int oldy = y;
        if (6-x > 0) {
            x++;
        } else if (6-x < 0) {
            x--;
        }

        if (6-y > 0) {
            y++;
        } else if (6-y < 0) {
            y--;
        }
        return make_pair(oldx, oldy);
    }
};

struct manager {
    vector<army> armies;

    ~manager() {
        for(auto army : armies) {
            delete(army.unit);
        }
    }

    RootRole::Player* find(int x, int y) {
        for (auto army : armies) {
            if (army.x == x && army.y == y)
                return army.unit;
        }
    }

    void kill(int x, int y) {
        int counter = 0;
        for (auto army : armies) {
            if (army.x == x && army.y == y) {
//                delete(army);
                armies.erase(armies.begin()+counter);
            } else {
                counter++;
            }
        }
    }
};
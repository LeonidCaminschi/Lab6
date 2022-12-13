#pragma once

#include "map.h"

struct Controller {
    Battlefield* alfa;

    Controller (Battlefield &a) {
        alfa = &a;
    }

    void start() {
        alfa->startBattle();
    }
};
#include "map.h"
#include "Controller.h"

using namespace Roles;

int main() {
    Battlefield alfa;
    Controller control(alfa);
    control.start();
}

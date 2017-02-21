#include "hal.h"

int main() {
    init();
    coil_drive();
    for(;;);
}

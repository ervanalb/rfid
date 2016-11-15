#include "hal.h"

int main() {
    init();
    drive_coil();
    for(;;);
}

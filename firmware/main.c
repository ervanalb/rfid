#include "hal.h"

static void delay() {
    static volatile int i;
    for(i=0; i<500000; i++);
}

int main() {
    init();
    drive_coil();
    for(;;) {
        if(button()) {
            read_on();
        } else {
            read_off();
        }
    }
}

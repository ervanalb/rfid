#include "button.h"
#include "hal.h"

#define BUTTON_REPS 100

int button_clicked() {
    static int button_n = 0;

    if(button()) {
        if(button_n < BUTTON_REPS) {
            button_n++;
            if(button_n == BUTTON_REPS) {
                return 1;
            }
        }
    } else {
        button_n = 0;
    }
    return 0;
}

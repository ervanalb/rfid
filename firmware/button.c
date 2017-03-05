#include "button.h"
#include "hal.h"

enum button_event button_event() {
    static enum {
        BUTTON_RELEASED,
        BUTTON_DEBOUNCE,
        BUTTON_PRESSED,
        BUTTON_STILL_PRESSED,
    } state = BUTTON_RELEASED;

    enum button_event retval = BUTTON_EVENT_NONE;

    switch(state) {
        case BUTTON_RELEASED:
            if(button()) {
                state = BUTTON_DEBOUNCE;
                button_timer = 5; // Debounce period 5ms
            }
            break;
        case BUTTON_DEBOUNCE:
            if(!button()) {
                state = BUTTON_RELEASED;
            } else if(button_timer == 0) {
                button_timer = 700; // Long press timer
                state = BUTTON_PRESSED;
            }
            break;
        case BUTTON_PRESSED:
            if(button_timer == 0) {
                retval = BUTTON_EVENT_LONG_PRESS;
                state = BUTTON_STILL_PRESSED;
            }
            else if(!button()) {
                retval = BUTTON_EVENT_PRESS;
                state = BUTTON_RELEASED;
            }
            break;
        case BUTTON_STILL_PRESSED:
            if(!button()) {
                state = BUTTON_RELEASED;
            }
            break;
    }

    return retval;
}

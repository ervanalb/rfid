#include "led.h"
#include "hal.h"

#define RAPID_BLINK_TIME 50
#define SLOW_BLINK_TIME 400

static enum which_led current_led;
static enum {
    LED_SOLID,
    LED_RAPID_BLINK,
    LED_SLOW_BLINK,
} state;

static int lit;

void led_set_current(enum which_led which) {
    current_led = which;
    state = LED_SOLID;
}

static void set_led(int state) {
    lit = state;
    switch(current_led) {
        case LED_READ:
            if(state) led_read_on(); else led_read_off();
            break;
        case LED_WRITE:
            if(state) led_write_on(); else led_write_off();
            break;
        case LED_SPOOF:
            if(state) led_spoof_on(); else led_spoof_off();
            break;
    }
}

void led_event(enum led_event event) {
    switch(event) {
        case LED_EVENT_ON:
            set_led(1);
            state = LED_SOLID;
            break;
        case LED_EVENT_OFF:
            set_led(0);
            state = LED_SOLID;
            break;
        case LED_EVENT_RAPID_BLINK:
            if(state != LED_RAPID_BLINK) {
                set_led(0);
                led_timer = RAPID_BLINK_TIME;
                state = LED_RAPID_BLINK;
            }
            break;
        case LED_EVENT_SLOW_BLINK:
            if(state != LED_SLOW_BLINK) {
                set_led(0);
                led_timer = SLOW_BLINK_TIME;
                state = LED_SLOW_BLINK;
            }
            break;
    }
}

void led() {
    switch(state) {
        case LED_SOLID:
            break;
        case LED_RAPID_BLINK:
            if(led_timer == 0) {
                set_led(!lit);
                led_timer = RAPID_BLINK_TIME;
            }
            break;
        case LED_SLOW_BLINK:
            if(led_timer == 0) {
                set_led(!lit);
                led_timer = SLOW_BLINK_TIME;
            }
            break;
    }
}

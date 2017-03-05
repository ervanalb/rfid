#pragma once

enum led_event {
    LED_EVENT_ON,
    LED_EVENT_OFF,
    LED_EVENT_RAPID_BLINK,
    LED_EVENT_SLOW_BLINK,
};

enum which_led {
    LED_READ,
    LED_WRITE,
    LED_SPOOF,
};

void led();
void led_set_current(enum which_led which);
void led_event(enum led_event event);

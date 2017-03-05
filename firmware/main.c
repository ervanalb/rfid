#include "main.h"
#include "hal.h"
#include "button.h"
#include "led.h"
#include "protocol.h"

enum state state = STATE_REMOTE;

int main() {
    protocol_change(&protocol_fns[0]);
    init();
    transition(STATE_READ);
    for(;;) {
        enum button_event button_ev = button_event();
        led();
        switch(state) {
            case STATE_READ:
                protocol->read();
                if(button_ev == BUTTON_EVENT_PRESS) transition(STATE_WRITE);
                else if(button_ev == BUTTON_EVENT_LONG_PRESS) protocol->trigger_read();
                break;
            case STATE_WRITE:
                protocol->write();
                if(button_ev == BUTTON_EVENT_PRESS) transition(STATE_SPOOF);
                else if(button_ev == BUTTON_EVENT_LONG_PRESS) protocol->trigger_write();
                break;
            case STATE_SPOOF:
                protocol->spoof();
                if(button_ev == BUTTON_EVENT_PRESS) transition(STATE_READ);
                else if(button_ev == BUTTON_EVENT_LONG_PRESS) protocol->trigger_spoof();
                break;
            case STATE_REMOTE:
                if(button_ev == BUTTON_EVENT_PRESS) transition(STATE_READ);
                break;
        }
    }
}

void transition(enum state new_state) {
    if(new_state == state) return;

    switch(state) {
        case STATE_READ:
            protocol->exit_read();
            break;
        case STATE_WRITE:
            protocol->exit_write();
            break;
        case STATE_SPOOF:
            protocol->exit_spoof();
            break;
        case STATE_REMOTE:
            break;
    }

    state = new_state;
    switch(new_state) {
        case STATE_READ:
            stream_write_disable();
            stream_read_disable();
            stream_read_enable();
            coil_drive();
            led_write_off();
            led_spoof_off();
            led_set_current(LED_READ);
            led_event(LED_EVENT_ON);
            protocol->enter_read();
            break;
        case STATE_WRITE:
            stream_write_disable();
            stream_read_disable();
            coil_drive();
            stream_write_enable();
            led_read_off();
            led_spoof_off();
            led_set_current(LED_WRITE);
            led_event(LED_EVENT_ON);
            protocol->enter_write();
            break;
        case STATE_SPOOF:
            stream_write_disable();
            stream_read_disable();
            coil_float();
            coil_tune();
            led_read_off();
            led_write_off();
            led_set_current(LED_SPOOF);
            led_event(LED_EVENT_ON);
            protocol->enter_spoof();
            break;
        case STATE_REMOTE:
            stream_write_disable();
            stream_read_disable();
            coil_float();
            coil_tune();
            led_read_off();
            led_write_off();
            led_spoof_off();
            led_event(LED_EVENT_OFF);
            break;
    }
}

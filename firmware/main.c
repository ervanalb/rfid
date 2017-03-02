#include "main.h"
#include "hal.h"
#include "button.h"
#include "protocol.h"

enum state state = STATE_REMOTE;

int main() {
    protocol_change(&protocol_fns[0]);
    init();
    transition(STATE_READ);
    for(;;) {
        switch(state) {
            case STATE_READ:
                protocol->read();
                if(button_clicked()) transition(STATE_WRITE);
                break;
            case STATE_WRITE:
                protocol->write();
                if(button_clicked()) transition(STATE_SPOOF);
                break;
            case STATE_SPOOF:
                protocol->spoof();
                if(button_clicked()) transition(STATE_READ);
                break;
            case STATE_REMOTE:
                if(button_clicked()) transition(STATE_READ);
                break;
        }
    }
}

void transition(enum state new_state) {
    if(new_state == state) return;
    state = new_state;
    switch(new_state) {
        case STATE_READ:
            stream_write_disable();
            stream_read_disable();
            stream_read_enable();
            coil_drive();
            led_read_on();
            led_write_off();
            led_spoof_off();
            break;
        case STATE_WRITE:
            stream_write_disable();
            stream_read_disable();
            coil_drive();
            stream_read_enable();
            led_read_off();
            led_write_on();
            led_spoof_off();
            break;
        case STATE_SPOOF:
            stream_write_disable();
            stream_read_disable();
            coil_float();
            coil_tune();
            led_read_off();
            led_write_off();
            led_spoof_on();
            break;
        case STATE_REMOTE:
            stream_write_disable();
            stream_read_disable();
            coil_float();
            coil_tune();
            led_read_off();
            led_write_off();
            led_spoof_off();
            break;
    }
}

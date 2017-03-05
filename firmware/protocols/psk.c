#include "psk.h"
#include "protocol.h"
#include "hal.h"
#include <string.h>
#include "led.h"

// READ

// Returns - if o1 < o2
// Returns + in o1 > o2
// Returns 0 in o1 = o2
static int cmp(int o1, int o2) {
    for(int i=0; i<protocol_state.psk.cycle_length; i++) {
        int8_t c = protocol_state.psk.decoded_bits[o1] - protocol_state.psk.decoded_bits[o2];
        if(c != 0) return c;
        o1++;
        if(o1 == protocol_state.psk.cycle_length) o1 = 0;
        o2++;
        if(o2 == protocol_state.psk.cycle_length) o2 = 0;
    }
    return 0;
}

// Returns - if ~o1 < o2
// Returns + in ~o1 > o2
// Returns 0 in ~o1 = o2
static int cmp_inv(int o1, int o2) {
    for(int i=0; i<protocol_state.psk.cycle_length; i++) {
        int8_t c = 1 - protocol_state.psk.decoded_bits[o1] - protocol_state.psk.decoded_bits[o2];
        if(c != 0) return c;
        o1++;
        if(o1 == protocol_state.psk.cycle_length) o1 = 0;
        o2++;
        if(o2 == protocol_state.psk.cycle_length) o2 = 0;
    }
    return 0;
}

static void valid_read() {
    int max_so_far = 0;
    int min_so_far = 0;
    memset(protocol_state.psk.decoded_bytes, 0, sizeof(protocol_state.psk.decoded_bytes));

    for(int i=1; i<protocol_state.psk.cycle_length; i++) {
        if(cmp(i, max_so_far) > 0) max_so_far = i;
        else if(cmp(i, min_so_far) < 0) min_so_far = i;
    }

    if(cmp_inv(max_so_far, min_so_far) < 0) {
        // Inverted max is smaller than min
        min_so_far = max_so_far;
        int o = min_so_far;
        for(int i=0; i<protocol_state.psk.cycle_length; i++) {
            protocol_state.psk.decoded_bits[o] = 1 - protocol_state.psk.decoded_bits[o];
            o++;
            if(o == protocol_state.psk.cycle_length) o = 0;
        }
    }
    
    int o = min_so_far;
    for(int i=0; i<protocol_state.psk.cycle_length; i++) {
        if(protocol_state.psk.decoded_bits[o]) {
            protocol_state.psk.decoded_bytes[i >> 3] |= 1 << (7 - (i & 7));
        }
        o++;
        if(o == protocol_state.psk.cycle_length) o = 0;
    }
}

static void read_new_bit(int8_t bit) {
    if(protocol_state.psk.decoded_bits[protocol_state.psk.decoded_bits_ptr] != bit) {
        protocol_state.psk.decoded_bits[protocol_state.psk.decoded_bits_ptr] = bit;
        protocol_state.psk.cycle.counter = 0;
        led_event(LED_EVENT_ON);
    }
    if(protocol_state.psk.cycle.counter >= 0) {
        protocol_state.psk.cycle.counter++;
        if(protocol_state.psk.cycle.counter >= protocol_state.psk.cycle_length * protocol_state.psk.repeats_until_valid) {
            valid_read();
            led_event(LED_EVENT_RAPID_BLINK);
            protocol_state.psk.cycle.counter = -1;
        }
    }
    protocol_state.psk.decoded_bits_ptr++;
    if(protocol_state.psk.decoded_bits_ptr >= protocol_state.psk.cycle_length) {
        protocol_state.psk.decoded_bits_ptr -= protocol_state.psk.cycle_length;
    }
}

void protocol_psk_init() {
    memset(&protocol_state.psk, 0, sizeof(protocol_state.psk));
    protocol_state.psk.hpf.alpha = 0.95 * 65536;
    protocol_state.psk.lpf.alpha = 0.10 * 65536;
    protocol_state.psk.demod.carrier = 1;
    protocol_state.psk.bit_width = 32;
    protocol_state.psk.cycle_length = 224;
    protocol_state.psk.repeats_until_valid = 3;

    protocol_state.psk.write_poweron_time = 1875;
    protocol_state.psk.write_programming_time = 1875;
    protocol_state.psk.write_one = 56;
    protocol_state.psk.write_zero = 24;
    protocol_state.psk.write_start_gap = 15;
    protocol_state.psk.write_gap = 10;
}

void protocol_psk_read() {
    int available = stream_read_available();
    if(available == 0) return;
    if(available > sizeof(protocol_state.psk.read_buffer) / sizeof(int16_t)) available = sizeof(protocol_state.psk.read_buffer) / sizeof(int16_t);
    stream_read(protocol_state.psk.read_buffer, available);

    for(int i=0; i<available; i++) {
        // HPF incoming samples
        int32_t sample = protocol_state.psk.read_buffer[i];
        int32_t hpf_sample = (protocol_state.psk.hpf.alpha * (protocol_state.psk.hpf.prev_y + sample - protocol_state.psk.hpf.prev_x)) >> 16;
        protocol_state.psk.hpf.prev_x = sample;
        protocol_state.psk.hpf.prev_y = hpf_sample;

        // Simplex demodulation using a RF/2 carrier
        int32_t demod_sample = hpf_sample * protocol_state.psk.demod.carrier;
        protocol_state.psk.demod.carrier *= -1;

        // LPF and threshold current sample
        int32_t lpf_sample = protocol_state.psk.lpf.prev_y + ((protocol_state.psk.lpf.alpha * (demod_sample - protocol_state.psk.lpf.prev_y)) >> 16);
        protocol_state.psk.lpf.prev_y = lpf_sample;
        int lpf_bit = (lpf_sample >= 0) ? 1 : 0;

        // Clock recovery
        protocol_state.psk.clock_recovery.t += 1;
        if(protocol_state.psk.clock_recovery.t >= protocol_state.psk.bit_width) {
            int32_t bit_val = protocol_state.psk.clock_recovery.bit_sum;
            read_new_bit(bit_val >= 0 ? 1 : 0);
            protocol_state.psk.clock_recovery.bit_sum = 0;
            protocol_state.psk.clock_recovery.t -= protocol_state.psk.bit_width;
        }
        protocol_state.psk.clock_recovery.bit_sum += demod_sample;
        if(lpf_bit != protocol_state.psk.clock_recovery.prev_lpf_bit) {
            protocol_state.psk.clock_recovery.prev_lpf_bit = lpf_bit;
            if(protocol_state.psk.clock_recovery.t == 0) {
            } else if(2*protocol_state.psk.clock_recovery.t < protocol_state.psk.bit_width) { // t < bit_width / 2
                protocol_state.psk.clock_recovery.t--;
            } else { // t >= bit_width / 2
                protocol_state.psk.clock_recovery.t++;
            }
        }

    }
}

void protocol_psk_enter_read() {
}

void protocol_psk_trigger_read() {
}

void protocol_psk_exit_read() {
}

// WRITE

static void write_gap() {
    protocol_state.psk.write_val = 0;
    protocol_state.psk.run_length = protocol_state.psk.write_gap;
}

static void write_bit(int bit) {
    protocol_state.psk.write_val = 1;
    protocol_state.psk.run_length = bit ? protocol_state.psk.write_one : protocol_state.psk.write_zero;
}

static void write_next() {
    switch(protocol_state.psk.write_state) {
        case WRITE_IDLE:
            protocol_state.psk.write_val = 1;
            protocol_state.psk.run_length = 0;
            return;
        case WRITE_POWERON:
            led_event(LED_EVENT_RAPID_BLINK);
            protocol_state.psk.blocks_to_write = 1 + (protocol_state.psk.cycle_length + 31) / 32;
            protocol_state.psk.write_block = 0;
            memset(protocol_state.psk.block_data, 0, sizeof(protocol_state.psk.block_data));
            for(int i=0; i < (protocol_state.psk.cycle_length + 7) / 8; i++) { // For each byte
                protocol_state.psk.block_data[i / 4 + 1] |= (uint32_t)protocol_state.psk.decoded_bytes[i] << ((3 - (i & 3)) * 8);
            }
            protocol_state.psk.block_data[0] = 0x000810e0;

            // Send a poweron sequence of 6250 1s
            protocol_state.psk.write_val = 1;
            protocol_state.psk.run_length = protocol_state.psk.write_poweron_time;
            protocol_state.psk.write_state = WRITE_START_GAP;
            return;
        case WRITE_START_GAP:
            // Send a start gap
            protocol_state.psk.write_bit = 0;
            protocol_state.psk.write_val = 0;
            protocol_state.psk.run_length = protocol_state.psk.write_start_gap;
            protocol_state.psk.write_state = WRITE_DATA;
            return;
        case WRITE_DATA:
            if(protocol_state.psk.write_val == 1) {
                write_gap();
                if(protocol_state.psk.write_bit == 37) {
                    protocol_state.psk.write_state = WRITE_PROGRAMMING_TIME;
                } else {
                    protocol_state.psk.write_bit++;
                }
                return;
            }
            protocol_state.psk.write_val = 1;
            switch(protocol_state.psk.write_bit) {
                case 0: // First opcode bit
                    write_bit(1);
                    return;
                case 1: // Second opcode bit (page)
                    write_bit(0);
                    return;
                case 2: // Lock bit
                    write_bit(0);
                    return;
                case 35: // addr[2]
                    write_bit(protocol_state.psk.write_block & 4);
                    return;
                case 36: // addr[1]
                    write_bit(protocol_state.psk.write_block & 2);
                    return;
                case 37: // addr[0]
                    write_bit(protocol_state.psk.write_block & 1);
                    return;
                default: // Block data
                {
                    uint32_t block_data = protocol_state.psk.block_data[protocol_state.psk.write_block];
                    write_bit(block_data & (1 << (34 - protocol_state.psk.write_bit)));
                    return;
                }
            }
        case WRITE_PROGRAMMING_TIME:
            // Allow some time for programming
            protocol_state.psk.write_val = 1;
            protocol_state.psk.run_length = protocol_state.psk.write_programming_time;
            protocol_state.psk.write_block++;
            if(protocol_state.psk.write_block == protocol_state.psk.blocks_to_write) {
                // Done
                led_event(LED_EVENT_ON);
                protocol_state.psk.write_state = WRITE_IDLE;
            } else {
                // Next block
                protocol_state.psk.write_state = WRITE_START_GAP;
            }
            return;
    }
}

void protocol_psk_write() {
    int available = stream_write_space();
    while(available > 0) {
        if(protocol_state.psk.run_length == 0) {
            write_next();
            if(protocol_state.psk.run_length == 0) return;
        }
        stream_write_byte(protocol_state.psk.write_val);
        protocol_state.psk.run_length--;
        available--;
    }
}

void protocol_psk_enter_write() {
     protocol_state.psk.write_state = WRITE_IDLE;
}

void protocol_psk_trigger_write() {
    if(protocol_state.psk.write_state == WRITE_IDLE) {
         protocol_state.psk.write_state = WRITE_POWERON;
    }
}

void protocol_psk_exit_write() {
}

// SPOOF

void protocol_psk_spoof() {
}

void protocol_psk_enter_spoof() {
}

void protocol_psk_trigger_spoof() {
}

void protocol_psk_exit_spoof() {
}


#include "psk.h"
#include "protocol.h"
#include "hal.h"
#include <string.h>

static void read_new_bit(int8_t bit) {
    protocol_state.psk.decoded_bits[protocol_state.psk.decoded_bits_ptr] = bit;
    protocol_state.psk.decoded_bits_ptr++;
    if(protocol_state.psk.decoded_bits_ptr > 2 * protocol_state.psk.cycle_length) {
        protocol_state.psk.decoded_bits_ptr -= 2 * protocol_state.psk.cycle_length;
    }
}

void protocol_psk_init() {
    memset(&protocol_state.psk, 0, sizeof(protocol_state.psk));
    protocol_state.psk.hpf.alpha = 0.95 * 65536;
    protocol_state.psk.lpf.alpha = 0.95 * 65536;
    protocol_state.psk.demod.carrier = 1;
    protocol_state.psk.bit_width = 32;
    protocol_state.psk.cycle_length = 224;
}

void protocol_psk_read() {
    int available = stream_read_available();
    if(available == 0) return;
    if(available < 256) return; // TEMP, REMOVE ME
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

void protocol_psk_write() {
}

void protocol_psk_spoof() {
}


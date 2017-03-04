#pragma once
#include <stdint.h>

void protocol_psk_init();
void protocol_psk_read();
void protocol_psk_write();
void protocol_psk_spoof();

struct protocol_psk_params {
};

struct protocol_psk_state {
    int bit_width;
    int cycle_length;
    int repeats_until_valid;

    int16_t read_buffer[512];
    struct {
        int32_t alpha; // Alpha as a 16.16 fixed point number
        int32_t prev_x;
        int32_t prev_y;
    } hpf;
    struct {
        int32_t carrier;
    } demod;
    struct {
        int32_t alpha; // Alpha as a 16.16 fixed point number
        int32_t prev_y;
    } lpf;
    struct {
        int32_t t;
        int32_t bit_sum;
        int32_t prev_lpf_bit;
    } clock_recovery;
    struct {
        int counter;
    } cycle;

    int8_t decoded_bits[224];
    int decoded_bits_ptr;
};

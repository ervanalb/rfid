#pragma once
#include <stdint.h>

void protocol_psk_init();
void protocol_psk_read();
void protocol_psk_write();
void protocol_psk_spoof();

struct protocol_psk_params {
};

struct protocol_psk_state {
    // SHARED
    int bit_width;
    int cycle_length;
    int repeats_until_valid;
    uint8_t decoded_bytes[28];

    // READER
    int16_t read_buffer[256];
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

    // WRITER
    int write_poweron_time;
    int write_programming_time;
    int write_one;
    int write_zero;
    int write_start_gap;
    int write_gap;

    int blocks_to_write;
    int8_t write_val;
    int run_length;
    enum {
        WRITE_POWERON,
        WRITE_START_GAP,
        WRITE_DATA,
        WRITE_PROGRAMMING_TIME,
        WRITE_DONE
    } write_state;
    uint32_t block_data[8];
    int write_bit;
    int write_block;
};

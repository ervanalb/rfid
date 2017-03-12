#pragma once
#include <stdint.h>

void protocol_psk_init();
void protocol_psk_read();
void protocol_psk_write();
void protocol_psk_spoof();

void protocol_psk_enter_read();
void protocol_psk_enter_write();
void protocol_psk_enter_spoof();

void protocol_psk_exit_read();
void protocol_psk_exit_write();
void protocol_psk_exit_spoof();

void protocol_psk_trigger_read();
void protocol_psk_trigger_write();
void protocol_psk_trigger_spoof();

struct protocol_psk_params {
    // SHARED
    int bit_width;
    int cycle_length;
    int repeats_until_valid;

    // READER
    int32_t hpf_alpha; // Alpha as a 16.16 fixed point number
    int32_t lpf_alpha; // Alpha as a 16.16 fixed point number

    // WRITER
    int write_poweron_time;
    int write_programming_time;
    int write_one;
    int write_zero;
    int write_start_gap;
    int write_gap;
};

struct protocol_psk_state {
    // SHARED
    uint8_t card_data[28];

    // READER
    int16_t read_buffer[128];
    struct {
        int32_t prev_x;
        int32_t prev_y;
    } hpf;
    struct {
        int32_t carrier;
    } demod;
    struct {
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

    struct {
        int8_t bits[224];
        int bits_ptr;
        uint16_t cyclotron[28];
    } decoder;

    // WRITER

    int blocks_to_write;
    int8_t write_val;
    int run_length;
    enum {
        WRITE_IDLE,
        WRITE_POWERON,
        WRITE_START_GAP,
        WRITE_DATA,
        WRITE_PROGRAMMING_TIME,
    } write_state;
    uint32_t block_data[8];
    int write_bit;
    int write_block;
};

#ifndef __HAL_H
#define __HAL_H

#include <stdint.h>

#define SD_TIMEOUT 0xFFF

void init();

void read_off();
void read_on();

void write_off();
void write_on();

void spoof_off();
void spoof_on();

uint8_t button();

void drive_coil();
void float_coil();

void tune_coil();
void detune_coil();

// TODO neaten up these names
int16_t items_to_read();
void read_items(uint16_t* hws, int n);
 
#endif

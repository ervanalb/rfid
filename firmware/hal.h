#ifndef __HAL_H
#define __HAL_H

#include <stdint.h>

#define SD_TIMEOUT 0xFFF

void init();

void led_read_off();
void led_read_on();
void led_write_off();
void led_write_on();
void led_spoof_off();
void led_spoof_on();

int button();

void coil_drive();
void coil_float();
void coil_tune();
void coil_detune();

void stream_read_enable();
void stream_read_disable();
void stream_write_enable();
void stream_write_disable();
int16_t stream_read_available();
void stream_read(uint16_t* hws, int n);
int16_t stream_write_space();
void stream_write(uint8_t* bytes, int n);

void set_latency(int16_t l);

extern volatile uint8_t stream_read_enabled;
extern volatile uint8_t stream_write_enabled;
 
#endif

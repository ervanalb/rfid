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
int stream_read_available();
void stream_read(int16_t* hws, int n);
int stream_write_space();
void stream_write(int8_t* bytes, int n);
void stream_write_byte(int8_t byte);

void set_latency(int16_t l);

extern volatile int stream_read_enabled;
extern volatile int stream_write_enabled;

extern volatile int led_timer;
extern volatile int button_timer;
 
#endif

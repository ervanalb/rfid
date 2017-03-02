#pragma once

#include "psk.h"

extern const struct protocol_fns {
    void (*init)();
    void (*read)();
    void (*write)();
    void (*spoof)();
} protocol_fns[];

extern union protocol_state {
    struct protocol_psk_state psk;
} protocol_state;

extern union protocol_params {
    struct protocol_psk_params psk;
} protocol_params;

extern const struct protocol_fns *protocol;

void protocol_change(const struct protocol_fns *new_protocol);

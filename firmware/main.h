#pragma once

enum state {
    STATE_READ,
    STATE_WRITE,
    STATE_SPOOF,
    STATE_REMOTE,
};

extern enum state state;

void transition(enum state new_state);

#include "protocol.h"

const struct protocol_fns protocol_fns[] = {
    {
        .init  = protocol_psk_init,
        .read  = protocol_psk_read,
        .write = protocol_psk_write,
        .spoof = protocol_psk_spoof,
    }
};

union protocol_state protocol_state;
union protocol_params protocol_params;

const struct protocol_fns *protocol;

void protocol_change(const struct protocol_fns *new_protocol) {
    protocol = new_protocol;
    protocol->init();
}

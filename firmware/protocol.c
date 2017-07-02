#include "protocol.h"

const struct protocol_fns protocol_fns[] = {
    {
        .name = PROTOCOL_PSK_NAME,
        .version = PROTOCOL_PSK_VERSION,

        .init  = protocol_psk_init,

        .read  = protocol_psk_read,
        .write = protocol_psk_write,
        .spoof = protocol_psk_spoof,

        .enter_read  = protocol_psk_enter_read,
        .enter_write = protocol_psk_enter_write,
        .enter_spoof = protocol_psk_enter_spoof,

        .exit_read  = protocol_psk_exit_read,
        .exit_write = protocol_psk_exit_write,
        .exit_spoof = protocol_psk_exit_spoof,

        .trigger_read  = protocol_psk_trigger_read,
        .trigger_write = protocol_psk_trigger_write,
        .trigger_spoof = protocol_psk_trigger_spoof,
    }
};

union protocol_state protocol_state;
union protocol_params protocol_params;

const struct protocol_fns *protocol;

void protocol_change(const struct protocol_fns *new_protocol) {
    protocol = new_protocol;
    protocol->init();
}

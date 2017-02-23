CONFIG_BASIC_DATA_BIT_RATE = {
    8:   0,
    16:  1,
    32:  2,
    40:  3,
    50:  4,
    64:  5,
    100: 6,
    128: 7,
}

CONFIG_BASIC_MODULATION = {
    "direct":  0,
    "psk1":    1,
    "psk2":    2,
    "psk3":    3,
    "fsk1":    4,
    "fsk2":    5,
    "fsk1a":   6,
    "fsk2a":   7,
    "manchester": 8,
    "biphase":    16,
}

CONFIG_BASIC_PSK_CF = {
    2: 0,
    4: 1,
    8: 2
}

RISE_ADJ = 0
START_GAP = (15 - RISE_ADJ)   # fifteen sample start gap
WRITE_GAP = (10 - RISE_ADJ)   # ten sample write gap
ZERO = (24 + ADJ)             # 24 samples for zero
ONE = (56 + ADJ)              # 56 samples for one
PROGRAMMING_TIME = 1875                   # 15 ms programming time

power_on = [0] * 6250 + [1] * 6250 # 50 ms
tail = [1] * 6250

def config_block_basic(bit_width=8, modulation="direct", max_block=0, psk_cf=2):
    config = 0
    config |= CONFIG_BASIC_DATA_BIT_RATE[bit_width] << 18
    config |= CONFIG_BASIC_MODULATION[modulation] << 12
    config |= CONFIG_BASIC_PSK_CF[psk_cf] << 10
    assert max_block in range(7)
    config |= max_block << 5
    print(bin(config))
    return struct.pack("<I", config)

def get_bits(num, width):
    return [int(c) for c in "{:0" + str(width) + "b}".format(num)]

def write_bit(bit):
    return ([1] * ONE if bit else [1] * ZERO) + [0] * WRITE_GAP

def write_block(page, block_id, code, lock=False):
    assert page in range(2)
    assert block_id in range(8)
    code_bits = get_bits(struct.unpack("<I", code), 32)
    lock = bool(lock)

    stream = [0] * START_GAP
    stream += write_bit(1)    # opcode 1
    stream += write_bit(page) # opcode 0
    stream += write_bit(lock) # lock bit

    for bit in code_bits: # 32 bits of data
        stream += write_bit(bit)

    for bit in get_bits(block_id, 3): # 3 bits of block_id
        stream += write_bit(bit)

    block_bits = "{:03b}".format(block_id)
    for bit in block_bits: # 3 bits of block_id
        stream += one if bit == "1" else zero
    stream += [1] * PROGRAMMING_TIME
    return stream

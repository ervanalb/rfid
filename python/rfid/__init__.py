import usb.core
import struct
import numpy as np
import sys

class RFID:
    VID = 0xffff
    PID = 0x2951

    CONTROL_IN  = 0xC1  # Host to device
    CONTROL_OUT = 0x41  # Device to host

    REQUEST_LED_READ     = 0x20
    REQUEST_LED_WRITE    = 0x21
    REQUEST_LED_SPOOF    = 0x22
    REQUEST_COIL_DRIVE   = 0x23
    REQUEST_COIL_TUNE    = 0x24
    REQUEST_STREAM_READ  = 0x25
    REQUEST_STREAM_WRITE = 0x26
    REQUEST_LATENCY      = 0x27

    def __init__(self):
        self.dev = usb.core.find(idVendor=self.VID, idProduct=self.PID)
        self.dev.set_configuration()

    def led_read(self, state):
        state = int(bool(state))
        self.dev.ctrl_transfer(self.CONTROL_OUT, self.REQUEST_LED_READ, state, 0, b"")

    def led_write(self, state):
        state = int(bool(state))
        self.dev.ctrl_transfer(self.CONTROL_OUT, self.REQUEST_LED_WRITE, state, 0, b"")

    def led_spoof(self, state):
        state = int(bool(state))
        self.dev.ctrl_transfer(self.CONTROL_OUT, self.REQUEST_LED_SPOOF, state, 0, b"")

    def coil_drive(self, state):
        state = int(bool(state))
        self.dev.ctrl_transfer(self.CONTROL_OUT, self.REQUEST_COIL_DRIVE, state, 0, b"")

    def coil_tune(self, state):
        state = int(bool(state))
        self.dev.ctrl_transfer(self.CONTROL_OUT, self.REQUEST_COIL_TUNE, state, 0, b"")

    def stream_read_enable(self, state):
        state = int(bool(state))
        self.dev.ctrl_transfer(self.CONTROL_OUT, self.REQUEST_STREAM_READ, state, 0, b"")

    def stream_write_enable(self, state):
        state = int(bool(state))
        self.dev.ctrl_transfer(self.CONTROL_OUT, self.REQUEST_STREAM_WRITE, state, 0, b"")

    def stream_read(self, count):
        result = self.dev.read(0x81, count * 2, timeout=int(count / 125 * 1.2 + 1000))
        values = struct.unpack("<{}H".format(len(result) // 2), result)
        values = np.array(values, dtype=np.float)
        return values

    def stream_write(self, data):
        data = struct.pack("<{}B".format(len(data)), *list(data))
        result = self.dev.write(0x02, data, timeout=int(len(data) / 125 * 1.2 + 1000))
        assert result == len(data)

    def set_latency(self, latency):
        self.dev.ctrl_transfer(self.CONTROL_OUT, self.REQUEST_LATENCY, latency, 0, b"")

def tune_latency(r):
    r.led_read(True)
    r.coil_drive(True)
    results = []
    for i in range(200, 300):
        r.set_latency(i)
        r.stream_read_enable(True)
        values = r.stream_read(4096)
        r.stream_read_enable(False)
        v = values[1024:-1024]
        v1 = values[::2]
        v2 = values[1::2]
        diff = v2 - v1
        result = (i, np.mean(v), np.std(v), np.std(diff))
        results.append(result)
        print(result)
    r.coil_drive(False)
    r.led_read(False)
    results = np.array(results)
    plt.plot(results[:,0], results[:,1])
    plt.plot(results[:,0], results[:,2])
    plt.plot(results[:,0], results[:,3])
    plt.show()

def psk_decoder(stream):
    LPF_ALPHA = 0.2 # dt / (RC + dt)

    odd = False
    lpf_prev = 0
    diff1 = False
    diff2 = True
    for sample in stream:
        if odd:
            lpf_prev = LPF_ALPHA * (sample - prev_even) + (1 - LPF_ALPHA) * lpf_prev
            diff3 = diff2
            diff2 = diff1
            diff1 = lpf_prev > 0
            yield sum((diff1, diff2, diff3)) > 1
        else:
            prev_even = sample
        odd = not odd

def fsk_decoder(stream, period):
    f = 1/period * 2 * pi

    s_1 = 0
    s_2 = 0
    for x in stream:
        s = x + 2 * cos(f) * s_1 - s_2
        y = s - cmath.exp(-1j*f) * s_1
        y_r = abs(y)
        yield y_r

        s_2 = s_1
        s_1 = s
        

def decoder(stream):
    PREAMBLE = 250
    PERIOD = 16
    LENGTH = 224
    MARGIN = 2

    while True:
        dwell = False
        count = 0
        while True:
            s = next(stream)
            if s != dwell:
                dwell = s
                count = 0
            else:
                count += 1
                if count > PREAMBLE:
                    break

        while next(stream) == dwell:
            pass

        bits = []
        for i in range(LENGTH):
            acc = 0
            cnt = 0
            for j in range(PERIOD):
                s = (next(stream) != dwell)
                if j >= MARGIN and j < PERIOD - MARGIN:
                    acc += s
                    cnt += 1
            bits.append(acc > cnt / 2)
        bytes_ = [int("".join(["1" if b else "0" for b in bits[i:i+8]]), 2) for i in range(0, len(bits), 8)]
        yield bytes_

if __name__ == "__main__":
    import matplotlib.pyplot as plt

    ADJ = 0
    power_on = [0] * 6250 + [1] * 6250 # 50 ms
    start_gap = [0] * (15 - ADJ) # fifteen sample start gap
    write_gap = [0] * (10 - ADJ) # ten sample write gap
    zero = [1] * (24 + ADJ) + write_gap# 24 samples for zero
    one = [1] * (56 + ADJ) + write_gap # 56 samples for one
    tail = [1] * 6250

    def write_block(page, block_id, code):
        assert page in range(2)
        assert len(code) == 32
        assert block_id in range(8)

        stream = []
        stream += power_on + start_gap
        stream += one # opcode 1
        stream += one if page == 1 else zero # opcode 0

        stream += zero # lock bit

        for bit in code: # 32 bits of data
            stream += one if bit else zero

        block_bits = "{:03b}".format(block_id)
        for bit in block_bits: # 3 bits of block_id
            stream += one if bit == "1" else zero
        stream += tail
        return stream

    config = [
        0, 0, 0, 0, # master key, 4 bits
        0, 0, 0, 0, 0, 0, 0, # spec requires 0
        0, 1, 0, # Data Bit Rate RF/32
        0, # spec requires 0
        0, 0, 0, 0, 1, # Modulation PSK1
        0, 0, # PSK frequency RF/2
        0, # answer on request = false
        0, # spec requires 0
        1, 1, 1, # max block 7
        0, # no PWD
        0, # sequence start marker
        0, # no fast downlink
        0, # no inverse data
        0, # no init delay
    ]

    from secret_key import *

    stream = []

    stream += write_block(1, 3, [0] * 32)

    stream += write_block(0, 0, config)

    blkid = 1

    code = [0] * 28

    for i in range(0, len(code), 4):
        bits = "".join("{:08b}".format(byte) for byte in code[i:i+4])
        bits = [1 if bit == "1" else 0 for bit in bits]
        stream += write_block(0, blkid, bits)
        blkid += 1

    r = RFID()

    #tune_latency(r)
    #r.set_latency(230)

    import time
    try:
        r.led_write(True)
        r.coil_drive(True)
        time.sleep(0.1)
        r.stream_write_enable(True)
        r.stream_write(stream)
        time.sleep(0.1)
        r.stream_write_enable(False)
        r.led_write(False)
        r.coil_drive(False)
        time.sleep(0.1)

        r.coil_drive(False)
        time.sleep(0.1)
        r.coil_drive(True)
        r.led_read(True)
        r.stream_read_enable(True)
        values = r.stream_read(2**16)
        r.stream_read_enable(False)
        r.led_read(False)
    finally:
        r.coil_drive(False)
        r.led_write(False)
        r.led_read(False)

    #v = values[2000:8000]
    #plt.plot(values, 'ro')
    #values1 = v[::2]
    #values2 = v[1::2]
    #values1_smooth = np.convolve([1,1,1,1,1,1,1,1], values1)
    #values2_smooth = np.convolve([1,1,1,1,1,1,1,1], values2)
    #plt.plot(values1_smooth)
    #plt.plot(values2_smooth)
    #plt.show()

    #values = values[2000:-100]
    if len(sys.argv) > 1:
        with open(sys.argv[1], "w") as f:
            f.write("".join(["{}\n".format(int(v)) for v in values]))
    values = list(psk_decoder(values))
    plt.plot(values)
    codes = list(decoder(iter(values)))
    for code in codes:
        print(" ".join(["{:#02x}".format(b) for b in code]))

    #plt.xticks(np.arange(0, len(values), 16))
    #plt.grid()
    plt.show()

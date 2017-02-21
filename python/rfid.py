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

    power_on = [0] * 6250 + [1] * 6250 # 50 ms
    start_gap = [0] * 8 # ten sample start gap
    write_gap = [0] * 8 # ten sample write gap
    zero = [1] * 24 # 24 samples for zero
    one = [1] * 56 # 56 samples for one
    tail = [1] * 6250 + power_on

    code = [0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0]

    stream = ([1] * 15 + [0] * 15) * 10000;

    #stream = []
    #stream += power_on + start_gap
    #stream += one + write_gap + zero + write_gap + zero + write_gap
    #for bit in code:
    #    stream += one if bit else zero
    #    stream += write_gap
    #stream += zero + write_gap + zero + write_gap + zero + write_gap
    #stream += tail

    stream = []
    stream += power_on + start_gap
    stream += one + write_gap + one + write_gap + zero + write_gap
    stream += zero + write_gap + zero + write_gap + zero + write_gap
    stream += [1] * 6250
    #stream += tail

    #stream = []
    #stream += power_on + start_gap
    #stream += zero + write_gap + zero + write_gap + tail

    r = RFID()
    try:
        r.led_write(True)
        r.stream_write_enable(True)
        r.stream_write(stream)
        import time
        time.sleep(0.1)
        r.stream_write_enable(False)
        r.led_write(False)
        r.led_read(True)
        r.stream_read_enable(True)
        values = r.stream_read(2**16)
        r.stream_read_enable(False)
        r.led_read(False)
    finally:
        r.coil_drive(False)
        r.led_write(False)
        r.led_read(False)

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

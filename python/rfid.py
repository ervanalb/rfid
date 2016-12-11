import usb.core
import struct
import numpy as np
import sys

class RFID:
    VID = 0xffff
    PID = 0x2951

    CONTROL_IN  = 0xC1  # Host to device
    CONTROL_OUT = 0x41  # Device to host

    REQUEST_DRIVE_COIL = 0x20

    def __init__(self):
        self.dev = usb.core.find(idVendor=self.VID, idProduct=self.PID)
        self.dev.set_configuration()

    def drive_coil(self, state):
        state = int(bool(state))
        self.dev.ctrl_transfer(self.CONTROL_OUT, self.REQUEST_DRIVE_COIL, state, 0, b"")

    def read_data(self):
        result = self.dev.read(0x81, 2**17, 1000)
        values = struct.unpack("<{}H".format(len(result) // 2), result)
        values = np.array(values, dtype=np.float)
        return values

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

    r = RFID()
    r.drive_coil(True)
    values = r.read_data()
    r.drive_coil(False)

    values = values[2000:-100]
    if len(sys.argv) > 1:
        with open(sys.argv[1], "w") as f:
            f.write("".join(["{}\n".format(int(v)) for v in values]))
    values = list(sk_decoder(values))
    plt.plot(values)
    codes = list(decoder(iter(values)))
    for code in codes:
        print(" ".join(["{:#02x}".format(b) for b in code]))

    #plt.xticks(np.arange(0, len(values), 16))
    #plt.grid()
    plt.show()

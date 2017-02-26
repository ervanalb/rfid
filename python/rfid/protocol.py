import numpy as np
from scipy import signal
import cmath
import math

FREQ = 125000.
NYQ_FREQ = FREQ / 2.

def hpf(data, cutoff=1000):
    b, a = signal.butter(1, cutoff / NYQ_FREQ, 'high')
    return signal.lfilter(b, a, data)

def lpf(data, cutoff=10000):
    b, a = signal.butter(1, cutoff / NYQ_FREQ, 'low')
    return signal.lfilter(b, a, data)

def thresh(data):
    return "".join("1" if bit > 0 else "0" for bit in data)

def demodulate(data, carrier):
    long_carrier = np.tile(carrier, len(data) // len(carrier) + 1)[0:len(data)]
    return data * long_carrier

def carrier(period, duty=0.5):
    return np.array([1. if i < period * duty else -1. for i in range(period)])

def psk_demodulator(data):
    data = hpf(data)
    data = demodulate(data, carrier(2))
    #data = lpf(data)
    return data

def fsk_demodulator(data, p0=8, p1=10, alpha=0.95):
    data0 = np.abs(goertzel(data, p0, alpha))
    data1 = np.abs(goertzel(data, p1, alpha))
    return hpf(data1 - data0)

def goertzel(stream, period, alpha=0.95):
    w0 = 1/period * 2 * math.pi

    a = [1, -2 * math.cos(w0) * alpha, alpha ** 2]
    b = [1]

    s = signal.lfilter(b, a, stream)

    a = [1]
    b = [1, -cmath.exp(-1j*w0)]

    y = signal.lfilter(b, a, s)

    return y

def decode_manchester(bits):
    carrier = ("01" * ((len(bits) + 1) // 2))[0:len(bits)]
    carrier = int(carrier, 2)
    signal = int(bits, 2)
    return ("{:0" + str(len(bits)) + "b}").format(carrier ^ signal)

def decoder(stream, bit_width=8):
    #stream = list(thresh(stream))
    resample_bits = lambda i: np.reshape(np.hstack(((stream[i:], np.zeros((-len(stream) + i) % bit_width)))), (-1, bit_width))

    resamp = [resample_bits(i) for i in range(bit_width)]
    strengths = [np.sum(np.sum(data, axis=1) ** 2) for data in resamp]
    i = strengths.index(max(strengths))
    decoded_bits = np.sum(resamp[i], axis=1) / bit_width
    decoded_waveform = np.hstack((np.zeros(i), np.reshape(np.tile(decoded_bits, bit_width), (bit_width, -1)).T.flatten()))
    return (decoded_bits, decoded_waveform)

def find_cycles(stream, length):
    match = 0
    cycle = ""
    for x in stream:
        if len(cycle) < length:
            cycle = cycle + x
            continue

        if cycle[0] == x:
            match += 1
            if match == length:
                yield cycle
                match = 0
        else:
            match = 0
        cycle = cycle[1:] + x

def sort_cycle(cycle, reverse_ok=True):
    shifted = lambda i: cycle[i:] + cycle[0:i]
    fromnum = lambda n: ("{:0" + str(len(cycle)) + "b}").format(n)

    numbers = [int(shifted(i), 2) for i in range(len(cycle))]
    if reverse_ok:
        numbers += [2**len(cycle)+~int(shifted(i), 2) for i in range(len(cycle))]
    best = min(numbers)
    return fromnum(best)

def bytes_to_binary_string(s):
    return "".join("{:08b}".format(b) for b in s)

def binary_string_to_bytes(s):
    n = int(s, 2)
    return bytes(reversed(bytes((n >> i) & 255 for i in range(0, len(s), 8))))

def pretty_bytes(s):
    return " ".join("{:02x}".format(b) for b in s)

#def decoder(stream):
#    PREAMBLE = 250
#    PERIOD = 16
#    LENGTH = 224
#    MARGIN = 2
#
#    while True:
#        dwell = False
#        count = 0
#        while True:
#            s = next(stream)
#            if s != dwell:
#                dwell = s
#                count = 0
#            else:
#                count += 1
#                if count > PREAMBLE:
#                    break
#
#        while next(stream) == dwell:
#            pass
#
#        bits = []
#        for i in range(LENGTH):
#            acc = 0
#            cnt = 0
#            for j in range(PERIOD):
#                s = (next(stream) != dwell)
#                if j >= MARGIN and j < PERIOD - MARGIN:
#                    acc += s
#                    cnt += 1
#            bits.append(acc > cnt / 2)
#        bytes_ = [int("".join(["1" if b else "0" for b in bits[i:i+8]]), 2) for i in range(0, len(bits), 8)]
#        yield bytes_

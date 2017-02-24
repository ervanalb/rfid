import numpy as np
from scipy import signal
import cmath

FREQ = 125000.
NYQ_FREQ = FREQ / 2.

def hpf(data, cutoff=1000):
    b, a = signal.butter(1, cutoff / NYQ_FREQ, 'high')
    return signal.lfilter(b, a, data)

def lpf(data, cutoff=10000):
    b, a = signal.butter(1, cutoff / NYQ_FREQ, 'low')
    return signal.lfilter(b, a, data)

def thresh(data):
    for x in data:
        if x > 0:
            yield 1
        else:
            yield -1

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

def fsk_demodulator(stream, period):
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

def decoder(stream, bit_width=8):
    #stream = list(thresh(stream))
    resample_bits = lambda i: np.reshape(np.hstack(((stream[i:], np.zeros((-len(stream) + i) % bit_width)))), (-1, bit_width))

    resamp = [resample_bits(i) for i in range(bit_width)]
    strengths = [np.sum(np.sum(data, axis=1) ** 2) for data in resamp]
    i = strengths.index(max(strengths))
    decoded_bits = np.sum(resamp[i], axis=1) / bit_width
    decoded_waveform = np.hstack((np.zeros(i), np.reshape(np.tile(decoded_bits, bit_width), (bit_width, -1)).T.flatten()))
    return (decoded_bits, decoded_waveform)

def find_cycles(stream, length=224):
    match = 0
    cycle = []
    for x in stream:
        if len(cycle) < length:
            cycle.append(x)
            continue

        if cycle[0] == x:
            match += 1
            if match == length:
                yield cycle
                match = 0
        else:
            match = 0
        cycle = cycle[1:] + [x]

def sort_cycle(cycle, reverse_ok=True):
    shifted = lambda i: np.hstack((cycle[i:], cycle[0:i]))
    tonum = lambda c: int("".join("1" if bit > 0 else "0" for bit in c), 2)
    fromnum = lambda n: ("{:0" + str(len(cycle)) + "b}").format(n)

    numbers = [tonum(shifted(i)) for i in range(len(cycle))]
    if reverse_ok:
        numbers += [2**len(cycle)+~tonum(shifted(i)) for i in range(len(cycle))]
    best = min(numbers)
    return fromnum(best)

def binary_string_to_bytes(s):
    n = int(s, 2)
    return bytes(reversed(bytes((n >> i) & 255 for i in range(0, len(s), 8))))

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

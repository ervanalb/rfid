import numpy as np
from scipy import signal
import cmath
import math

FREQ = 125000.
NYQ_FREQ = FREQ / 2.

def hpf(data, cutoff=62.5):
    b, a = signal.butter(1, 2 / cutoff, 'high')
    return signal.lfilter(b, a, data)

def lpf(data, cutoff=6.25):
    b, a = signal.butter(1, 2 / cutoff, 'low')
    return signal.lfilter(b, a, data)

def thresh(data):
    return "".join("1" if bit > 0 else "0" for bit in data)

def sine_sqw(x, period):
    x = x % period
    if x == 0 or x == period / 2:
        return 0.
    elif x < period / 2:
        return 1.
    else:
        return -1.

def cosine_sqw(x, period):
    return sine_sqw(x + period / 4, period)

def carrier(period, length):
    return np.cos((np.arange(length) % period) * 2 * np.pi / period)

def complex_carrier(period, length):
    return np.exp(1j * (np.arange(length) % period) * 2 * np.pi / period)

def psk_demodulator(data):
    data = hpf(data)
    data = data * carrier(2, len(data))
    #data = lpf(data)
    return data

def fsk_demodulator(data, p0=10, p1=8, alpha=0.95):
    data0 = np.abs(goertzel(data, p0, alpha))
    data1 = np.abs(goertzel(data, p1, alpha))
    return hpf(data1 - data0, 1000)

def goertzel(stream, period, alpha=0.95):
    w0 = 1/period * 2 * math.pi

    #a = [1, -2 * math.cos(w0) * alpha, alpha ** 2]
    #b = [1]

    #s = signal.lfilter(b, a, stream)

    #a = [1]
    #b = [1, -cmath.exp(-1j*w0)]

    #y = signal.lfilter(b, a, s)

    y = signal.lfilter([1], [1, -alpha * cmath.exp(1j*w0)], stream)

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

def simple_decoder(stream, bit_width=8):
    bits = thresh(lpf(stream))
    t = 0
    last_b = bits[0]
    t_arr = []
    w_arr = []
    b_arr = []
    bit_sum = 0
    bit_count = 0
    for b, s in zip(bits, stream):
        t = t + 1
        if t >= bit_width:
            bit_val = bit_sum / bit_count
            w_arr += [bit_val] * bit_count
            b_arr.append(bit_val)
            bit_sum = 0
            bit_count = 0
            t -= bit_width
        t_arr.append(t)

        bit_sum += s
        bit_count += 1
        if b != last_b:
            last_b = b
            if t > 0 and t < bit_width / 2:
                t -= 1
            if t >= bit_width / 2:
                t += 1
    return (np.array(t_arr), np.array(w_arr), np.array(b_arr))

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

import sys
import numpy as np
import matplotlib.pyplot as plt
from math import *
import cmath

data = (int(line) for line in sys.stdin)

def hpf(data):
    ALPHA = 0.7

    y = 0
    lx = 0
    for x in data:
        y = ALPHA * (y + x - lx)
        yield y
        lx = x

def lpf(data):
    ALPHA = 0.001

    y = 0
    for x in data:
        y = ALPHA * x + (1 - ALPHA) * y
        yield y

def thresh(data):
    x2 = 0
    x3 = 0

    for x in data:
        yield int(sum((x > 0, x2 > 0, x3 > 0)) > 1)
        x2 = x
        x3 = x2

def rle(data):
    prev = None
    for x in data:
        if x != prev:
            if prev is not None:
                yield ctr
            ctr = 0
            prev = x
        ctr += 1

def fsk_decoder(stream, period):
    ALPHA = 0.95

    f = 1/period * 2 * pi

    s_1 = 0
    s_2 = 0
    for x in stream:
        s = x + 2 * cos(f) * s_1 * ALPHA - s_2 * ALPHA ** 2
        y = s - cmath.exp(-1j*f) * s_1
        #y_r = abs(y) * BETA + y_r_1 * (1 - BETA)
        y_r = abs(y) ** 2
        yield y_r

        s_2 = s_1
        s_1 = s

def evenodd(stream):
    odd = False
    for x in stream:
        if odd:
            yield x - prev_even
            yield x - prev_even
        else:
            prev_even = x
        odd = not odd

def selector(data2, data5, data8, data10):
    THRESH = 500000
    for (d2, d5, d8, d10) in zip(lpf(data2), lpf(data5), lpf(data8), lpf(data10)):
        opts = (
            ("psk", d2 * 50),
            ("fsk1", d8 + d5),
            ("fsk2", d8 + d10)
        )
        kind, value = max(opts, key=lambda x: x[1])
        if value < THRESH:
            yield None
        else:
            yield kind

def dispatch(encodings):
    prev_encoding = None
    for i in range(len(encodings)):
        if encodings[i] != prev_encoding:
            if prev_encoding != None:
                yield (prev_encoding, start, i)
            prev_encoding = encodings[i]
            start = i
    if prev_encoding != None:
        yield (prev_encoding, start, i)

def decode_fsk(stream):
    for x in stream:
        if x > 0:
            yield 1
        else:
            yield 0

def decode_psk(stream):
    for x in stream:
        if x > 0:
            yield 1
        else:
            yield 0

data = list(data)
data_hpf = list(hpf(data))
data2 = list(fsk_decoder(data_hpf, 2))

data = list(data)
data_hpf = list(hpf(data))
data2 = list(fsk_decoder(data_hpf, 2))
data5 = list(fsk_decoder(data_hpf, 5))
data8 = list(fsk_decoder(data_hpf, 8))
data10 = list(fsk_decoder(data_hpf, 10))
encodings = list(selector(data2, data5, data8, data10))

for (encoding, start, end) in dispatch(encodings):
    print(encoding, start, end)
    if encoding == "psk":
        result = decode_psk(evenodd(data_hpf[start:end]))
    elif encoding == "fsk1":
        result = decode_fsk(np.array(data8[start:end]) - np.array(data5[start:end]))
    elif encoding == "fsk2":
        result = decode_fsk(np.array(data8[start:end]) - np.array(data10[start:end]))

result = list(result)

plt.plot(result)
plt.show()
#plt.plot(data5[0:1000], 'r-')
#plt.plot(data8[0:1000], 'g-')
#plt.plot(data10[0:1000], 'b-')
#plt.plot(data2[0:1000], 'y-')
#plt.plot(np.array(data)[0:1000] * 2, 'ko-')


#data = list(thresh(bpf(data)))
#data2 = list(bpf(data))
#rle_data = list(rle(data))
#plt.plot(rle_data, 'o-')
#plt.plot(data[1000:2000], 'o-')
#plt.plot(data2[1000:2000], 'o-')
plt.show()

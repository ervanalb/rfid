import cmath

def hpf(data, alpha=0.7):
    y = 0
    lx = 0
    for x in data:
        y = alpha * (y + x - lx)
        yield y
        lx = x

def lpf(data, alpha=0.2):
    y = 0
    for x in data:
        y = alpha * x + (1 - alpha) * y
        yield y

def thresh(data):
    for x in data:
        if x > 0:
            yield 1
        else:
            yield -1

def demodulate(data, carrier):
    for (s1, s2) in zip(data, carrier):
        yield s1 * s2

def carrier(period, duty=0.5):
    while True:
        for i in range(period):
            yield 1 if i < period * duty else -1

def psk_demodulator(data):
    data = hpf(data)
    data = demodulate(data, carrier(2))
    data = lpf(data)
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
    resample_bits = lambda i: [stream[j:j+bit_width] for j in range(i, len(stream), bit_width)]
    square_of_sum = lambda data: sum([sum(bit)**2 for bit in data])

    resamp = [resample_bits(i) for i in range(bit_width)]
    strengths = [square_of_sum(data) for data in resamp]
    i = strengths.index(max(strengths))
    decoded_bits = [sum(bit) / bit_width for bit in resamp[i]]
    decoded_waveform = ([0] * i) + [bit for bit in decoded_bits for _ in range(bit_width)]
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
    shifted = lambda i: cycle[i:] + cycle[0:i]
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

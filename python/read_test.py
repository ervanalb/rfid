import rfid
import matplotlib.pyplot as plt

r = rfid.RFID()
samples = r.raw_read(2**15)
samples_demod = rfid.psk_demodulator(samples)
(decoded_bits, decoded_waveform) = rfid.decoder(samples_demod, bit_width=32)
plt.plot(list(samples_demod))
plt.plot(list(decoded_waveform))
plt.show()
cycles = list(rfid.find_cycles(rfid.thresh(decoded_bits), length=224))

seen = {}
for cycle in cycles:
    cycle_bytes = rfid.binary_string_to_bytes(rfid.sort_cycle(cycle))
    seen[cycle_bytes] = seen.get(cycle_bytes, 0) + 1

for (cycle, count) in seen.items():
    print("Read {} times: {}".format(count, rfid.pretty_bytes(cycle)))

import rfid
import matplotlib.pyplot as plt

r = rfid.RFID()
samples = r.raw_read(2**17)
samples = samples[-2**15:]
samples = rfid.hpf(samples)
plt.plot(samples, 'ro')
#samples_demod = rfid.fsk_demodulator(samples, p0=8, p1=10)
samples_demod = rfid.psk_demodulator(samples)
#(decoded_bits, decoded_waveform) = rfid.decoder(samples_demod, bit_width=32)
(clock_recovery, decoded_waveform, decoded_bits) = rfid.simple_decoder(samples_demod, bit_width=32)
plt.plot(samples_demod)
#plt.plot(clock_recovery)
plt.plot(decoded_waveform)
plt.show()
cycles = rfid.find_cycles(rfid.thresh(decoded_bits), length=224)

seen = {}
for cycle in cycles:
    cycle_bytes = rfid.binary_string_to_bytes(rfid.sort_cycle(cycle))
    seen[cycle_bytes] = seen.get(cycle_bytes, 0) + 1

for (cycle, count) in seen.items():
    print("Read {} times: {}".format(count, rfid.pretty_bytes(cycle)))

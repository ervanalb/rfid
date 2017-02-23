import rfid
import matplotlib.pyplot as plt

r = rfid.RFID()
samples = r.raw_read(2**15)
#samples_hpf = rfid.hpf(samples)
samples_demod = list(rfid.psk_demodulator(samples))
(decoded_bits, decoded_waveform) = rfid.decoder(list(samples_demod), bit_width=32)
#plt.plot(list(samples_hpf))
plt.plot(list(samples_demod))
plt.plot(list(decoded_waveform))
plt.show()
cycles = list(rfid.find_cycles(rfid.thresh(decoded_bits)))
for cycle in cycles:
    print(rfid.binary_string_to_bytes(rfid.sort_cycle(cycle)))

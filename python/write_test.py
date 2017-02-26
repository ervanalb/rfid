import rfid
import rfid.t5577
import matplotlib.pyplot as plt

data = bytes([0, 0, 0x03, 0x55] * 7)

print("Writing", rfid.pretty_bytes(data))

data_sorted = rfid.binary_string_to_bytes(rfid.sort_cycle(rfid.bytes_to_binary_string(data)))
if data_sorted != data:
    print("Warning! Data cycles to", rfid.pretty_bytes(data_sorted))

r = rfid.RFID()
samples = rfid.t5577.write_card_basic(data, bit_width=50, modulation="fsk1")
r.raw_write(samples)

samples = r.raw_read(2**15)
samples_demod = rfid.fsk_demodulator(samples)
(decoded_bits, decoded_waveform) = rfid.decoder(samples_demod, bit_width=50)
plt.plot(samples_demod)
plt.plot(decoded_waveform)
plt.show()
cycles = rfid.find_cycles(rfid.thresh(decoded_bits), length=96)
for cycle in cycles:
    cycle_bytes = rfid.binary_string_to_bytes(rfid.sort_cycle(cycle))
    if cycle_bytes == data_sorted:
        print("Read back OK!")
    else:
        print("Bad read:", rfid.pretty_bytes(cycle_bytes))

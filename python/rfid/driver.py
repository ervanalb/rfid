import usb.core
import struct
import numpy as np
import sys

class RFID:
    VID = 0xffff
    PID = 0x2951

    CONTROL_IN  = 0xC1  # Host to device
    CONTROL_OUT = 0x41  # Device to host

    REQUEST_LED_READ     = 0x20
    REQUEST_LED_WRITE    = 0x21
    REQUEST_LED_SPOOF    = 0x22
    REQUEST_COIL_DRIVE   = 0x23
    REQUEST_COIL_TUNE    = 0x24
    REQUEST_STREAM_READ  = 0x25
    REQUEST_STREAM_WRITE = 0x26
    REQUEST_LATENCY      = 0x27

    def __init__(self):
        self.dev = usb.core.find(idVendor=self.VID, idProduct=self.PID)
        self.dev.set_configuration()

    def led_read(self, state):
        state = int(bool(state))
        self.dev.ctrl_transfer(self.CONTROL_OUT, self.REQUEST_LED_READ, state, 0, b"")

    def led_write(self, state):
        state = int(bool(state))
        self.dev.ctrl_transfer(self.CONTROL_OUT, self.REQUEST_LED_WRITE, state, 0, b"")

    def led_spoof(self, state):
        state = int(bool(state))
        self.dev.ctrl_transfer(self.CONTROL_OUT, self.REQUEST_LED_SPOOF, state, 0, b"")

    def coil_drive(self, state):
        state = int(bool(state))
        self.dev.ctrl_transfer(self.CONTROL_OUT, self.REQUEST_COIL_DRIVE, state, 0, b"")

    def coil_tune(self, state):
        state = int(bool(state))
        self.dev.ctrl_transfer(self.CONTROL_OUT, self.REQUEST_COIL_TUNE, state, 0, b"")

    def stream_read_enable(self, state):
        state = int(bool(state))
        self.dev.ctrl_transfer(self.CONTROL_OUT, self.REQUEST_STREAM_READ, state, 0, b"")

    def stream_write_enable(self, state):
        state = int(bool(state))
        self.dev.ctrl_transfer(self.CONTROL_OUT, self.REQUEST_STREAM_WRITE, state, 0, b"")

    def stream_read(self, count):
        result = self.dev.read(0x81, count * 2, timeout=int(count / 125 * 1.2 + 1000))
        values = struct.unpack("<{}H".format(len(result) // 2), result)
        values = np.array(values, dtype=np.float)
        return values

    def stream_write(self, data):
        data = struct.pack("<{}B".format(len(data)), *list(data))
        result = self.dev.write(0x02, data, timeout=int(len(data) / 125 * 1.2 + 1000))
        assert result == len(data)

    def set_latency(self, latency):
        self.dev.ctrl_transfer(self.CONTROL_OUT, self.REQUEST_LATENCY, latency, 0, b"")

    # Higher-level functions

    def raw_read(self, n_samples):
        try:
            self.led_read(True)
            self.coil_drive(True)
            self.stream_read_enable(True)
            return self.stream_read(n_samples)
        finally:
            self.stream_read_enable(False)
            self.coil_drive(False)
            self.led_read(False)

    def raw_write(self, samples):
        try:
            self.led_write(True)
            self.stream_write_enable(True)
            self.stream_write(samples)
        finally:
            self.stream_write_enable(False)
            self.coil_drive(False)
            self.led_write(False)


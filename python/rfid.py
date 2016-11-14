import usb.core

class RFID:
    VID = 0xffff
    PID = 0x2951

    CONTROL_IN  = 0xC1  # Host to device
    CONTROL_OUT = 0x41  # Device to host

    REQUEST_DRIVE_COIL = 0x20

    def __init__(self):
        self.dev = usb.core.find(idVendor=self.VID, idProduct=self.PID)
        self.dev.set_configuration()

    def drive_coil(self, state):
        state = int(bool(state))
        self.dev.ctrl_transfer(self.CONTROL_OUT, self.REQUEST_DRIVE_COIL, state, 0, b"")

if __name__ == "__main__":
    import time

    r = RFID()
    r.drive_coil(True)
    time.sleep(3)
    r.drive_coil(False)

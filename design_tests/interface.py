import serial
import time
import sys

class Chip:
    def __init__(self, serial_port, baud=115200, delay=0.001):
        self.port = serial.Serial(serial_port, baud, timeout=0)
        self.reset = False
        self.out_state = 0x000
        self.in_state  = 0x000
        self.delay = delay

    def get_all_outputs(self):
        return self.in_state

    def get_output(self, index):
        assert index >= 0 and index < 12

        o = self.in_state
        o = o & (1 << index)
        return (o != 0)

    def _push_outputs(self, step=False):
        lo = self.out_state & 0xFF
        hi = (
            ((self.out_state >> 8) & 0xF) | 
            ((self.reset & 0x1) << 4) |
            ((step & 0x1) << 5) |
            (0x0 << 6)
        )
        chk = ((hi+lo ^ 0xAB) & 0xFF)
        
        self.port.read(9999)
        self.port.write([0x5B, hi, lo, chk])
        time.sleep(self.delay)
        dat = bytearray()
        while len(dat) < 3:
            dat += self.port.read(9999)
        
        hi, lo, chk = dat[-3:]
        
        if (chk != (((hi+lo) ^ 0xAB) & 0xFF)) or ((hi & 0x40) == 0):
            print("CHECKSUM FAILURE")
            sys.exit(1)
        
        self.in_state = ((hi & 0xF) << 8) | (lo & 0xFF)

    def set_input(self, index, value):
        value_n = int(not (int(value) & 0x1))
        self.out_state |= (1 << index)
        self.out_state ^= (value_n << index)
        self._push_outputs()

    def set_all_inputs(self, value):
        value = value & 0xFFF
        self.out_state = value
        self._push_outputs()

    def set_reset(self, value):
        self.reset = value & 0x1
        self._push_outputs()

    def step_clock(self, n=1):
        for _ in range(n):
            self._push_outputs(step=True)
            
    def reset_sequence(self):
        # accounts for the sync delay in the reset line
        self.set_reset(1)
        self.step_clock(10)
        self.set_reset(0)
        self.step_clock(5)
#!/usr/bin/env python
from interface import *
import sys

## Test code for design 2 (counter)
c = Chip(sys.argv[1], 115200)

c.step_clock(10)

c.set_all_inputs(0b01)

c.reset_sequence()

print(c.get_all_outputs())
c.step_clock()
print(c.get_all_outputs())

c.set_all_inputs(0b11)
print(c.get_all_outputs())
c.step_clock()
c.step_clock()
print(c.get_all_outputs())
assert c.get_all_outputs() == 0xFFF

c.set_all_inputs(0b01)

def test_ctr():
    x = c.get_all_outputs()
    c.step_clock()
    assert c.get_all_outputs() == (x+1) & 0xFFF

# Verify that nothing breaks over many iterations
for _ in range(50):
    test_ctr()

# verify re-reset works

c.set_all_inputs(0b01)

c.reset_sequence()

print(c.get_all_outputs())
c.step_clock()
print(c.get_all_outputs())

c.set_all_inputs(0b11)
print(c.get_all_outputs())
c.step_clock()
c.step_clock()
print(c.get_all_outputs())
assert c.get_all_outputs() == 0xFFF

print("SUCCESS - COUNTER")

#!/usr/bin/env python
from interface import *
import sys

## Test code for design 2 (counter)
c = Chip(sys.argv[1], 115200)

c.step_clock(10)
c.reset_sequence()

def test_inputs(a, b):
    assert (a >= 0) and (a <= 0b111111)
    c.set_all_inputs((a << 6) | b)

    c.step_clock()

    x = c.get_all_outputs()
    assert x == (a + b), f"{x} {a} {b}"

test_inputs(0, 0)
print(c.get_all_outputs())
test_inputs(1, 1)
print(c.get_all_outputs())
test_inputs(63, 63)
print(c.get_all_outputs())
test_inputs(0, 63)
print(c.get_all_outputs())
test_inputs(63, 0)
print(c.get_all_outputs())
test_inputs(0b101010, 0b101010)
print(c.get_all_outputs())
test_inputs(0b010101, 0b010101)
print(c.get_all_outputs())
test_inputs(0b010101, 0b101010)
print(c.get_all_outputs())
test_inputs(0b101010, 0b010101)
print(c.get_all_outputs())

for x in [0, 1, 2, 4, 8, 16, 32]:
    for y in [0, 1, 2, 4, 8, 16, 32]:
        test_inputs(x, y)

print(x)

print("SUCCESS - ADDER")

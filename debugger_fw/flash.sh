#!/bin/sh
arduino-cli compile --upload --fqbn arduino:samd:adafruit_circuitplayground_m0 --port $1

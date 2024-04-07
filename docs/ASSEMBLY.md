---
geometry: margin=3cm
---

# Board Assembly Instructions

## Ordering Boards

Boards are ordered from JLCPCB using their PCBA service. Part IDs on LCSC are added to the KiCAD schematic and can be used to generate assembly files using KiCAD JLC plugin and/or using Excel (note that some parts may need to be swapped out due to stock reasons). Assembly quality has been fairly good so far, though some parts need to be manually rotated in the online JLC viewer because they don't always align correctly. It is recommended to pay the few dollars extra for board cleaning + extra padded packaging.

## Soldering Debugger Boards

JLC is able to populate all surface-mount components except for the M.2 standoff (in theory they can handle this as well, but we've had issues in the past with them not understanding how screws work). After receiving boards from JLC, they are populated as follows:

(TODO: insert picture of fresh board from JLC)

For each board:

1. Inspect all solder joints for quality, bridging, or major orientation issues. JLC quality is good but not perfect, and occasionally parts are oriented incorrectly or have solder bridges:

(TODO: insert picture of upside down chip)

2. Solder the standoff. Because of the metal mass, it requires a lot more heat than you'd expect. You'll want to clamp down the board and use a tweezer to push down on the standoff (make sure it sits flat) while you melt the solder.

3. (Optionally) solder a 30-pin male header + 2-pin male reset header. Otherwise, include a 30-pin header in the kit for students to solder if they need it. Other unpopulated headers (the flash chip, XCLK SMA, and HKSPI) can stay unpopulated.

## Soldering ASIC Breakouts

The ASIC breakouts can be ordered in panels (JLC will claim they can't panelize V-scored boards but they will do it just fine if you include it in the notes). See the SparkFun tutorial [How to Design a MicroMod Processor Board](https://learn.sparkfun.com/tutorials/designing-with-micromod/all#how-to-design-a-micromod-processor-board) and the [SparkFun KiCAD Panelizer](https://github.com/sparkfun/SparkFun_KiCad_Panelizer) + a stencil. For export-controls + risk reasons we assemble the chips onto the boards locally rather than shipping the chips overseas.

(TODO: insert picture of one full panel fresh from fab + picture of stencil)

1. Apply paste to the panel using the stencil. Some bridging is OK, but ensure there is not execess paste at a thickness greater than that of the stencil.

2. Load correctly-oriented chips and 0.1uF 0603 capacitors onto the breakouts and reflow.

3. If possible, inspect breakout under the X-Ray to verify no bridging. This is easiest to do _before_ depanelizing. Additionally, inspect visually to ensure no excess solder or subtle bridging between pins.

4. Depanelize the breakouts to prepare them for the next step.

## Flashing Setup

Before starting the flashing/test process:

1. Load Adafruit Circuit Playground (TODO: which one??) bootloader onto a micro-SD card. Load Arduino flasher (flash_from_SD) onto Arduino MKR Zero and insert SD card. May need to update the pins in `flash_from_SD` to match the pins on your board. For more details see the [relevant Adafruit documentation](https://learn.adafruit.com/programming-an-m0-using-an-arduino/overview).

2. Wire up the Tag-Connect to your Arduino. The pins you need are SWD, SWC, RESETn, 3V3, and GND. Following is the pinout of the Tag-Connect on the board (hole pattern is asymmetric and can be used to orient).

![](tagconnect.png)

3. (Optionally) use an external current-limited PSU to provide 3V3 rail for the Tag-Connect. Otherwise it can use the Arduino's 3V3 rail. If using PSU, make sure Arduino's ground pin is connected too, to prevent ground-loops.

4. (Optionally) get a USB inline current monitor and prepare a USB-C cable for powering the boards; this can make it easier to catch short-circuit conditions.

5. Open up a serial terminal with auto-reconnect (such as CoolTerm) and connect to the Arduino at 115200 baud. Resetting the Arduino should cause CoolTerm to disconnect, then reconnect, then print a "attempting to flash" message.

## Flashing Each Board

1. Insert ASIC breakout into the slot at a 45 degree angle, gently tighten the screw (avoid torquing too much). Verify that the breakout is sitting flat and aligned correctly with the connector (if it is too much of an angle, pins can short to other pins).

(TODO: insert image of alignment)

2. Connect Tag-Connect to the board. Do NOT connect USB to the board. Verify that current-draw (on the PSU or USB power meter) does not spike past \~200mA. Verify that 1v8, 3v3, and "power" LEDs are all lit up.

3. While holding down the Tag-Connect, press reset button on the Arduino (not the debugger) to flash it. It should print a success message to the serial port after completion.

4. Disconnect the Tag-Connect. Connect USB-C to the board. Verify that 1v8, 3v3, and "power" LEDs light up and that current-draw is reasonable.

5. Check if the board's serial port enumerates using `lsusb` or similar. Use Arduino IDE or CLI to flash serial-remote control code. In `debugger_fw/serial_remote`:

```
arduino-cli compile --upload --fqbn arduino:samd:adafruit_circuitplayground_m0 --port /dev/ttyWHATEVER
```

6. Set the board to the "Counter" project (binary 00001000 starting from the bottom). Run `test_counter.py` which will test all 12 outputs + clock + reset.

7. Set the board to the "Adder" project (binary 00000100 starting from the bottom). Run `test_adder.py` which will test all 12 inputs.

8. Unplug the board, apply a QC-pass sticker, and place it in the antistatic bag / bubble wrap. If headers were not previously soldered, include a 30-pin male header, a 2-pin male header, and a 2-pin jumper.



#include <Arduino.h>
#include "chip_interface.h"

void setup() {
    Serial.begin(115200);
    init_portio();

    // Step the clock a few times to get the design selected
    step_clock(10);

    // Test the adder design (idx = 1)
    while (true) {
        int x1 = rand() & 0x3F;
        int x2 = rand() & 0x3F;

        set_inputs(x1, 11, 6);
        set_inputs(x2, 5, 0);
        int out = get_outputs(6, 0);

        Serial.print("in1 = ");
        Serial.print(x1);
        Serial.print(" in2 = ");
        Serial.print(x2);
        Serial.print(" out = ");
        Serial.print(out);
        Serial.print((out == x1+x2) ? " CORRECT" : " INCORRECT");
        Serial.println();

        delay(250);
    }
}

void loop() { }

/**
 * Summary of use:
 * - void init_portio()
 *      - configure the I/O config
 *
 * - void set_status_led(bool val)
 *      - set the onboard status LED
 *
 * - void set_input(int idx, bool val)
 *      - equivalent to `inputs[idx] = val`
 *
 * - bool get_output(int idx)
 *      - equivalent to `return outputs[idx]`
 *
 * - void set_inputs(uint32_t vals, int hi, int lo)
 *      - equivalent to `inputs[hi:lo] = vals`
 *
 * - uint32_t get_outputs(int hi, int lo)
 *      - equivalent to `return outputs[hi:lo]`
 *
 * - void set_reset(bool val)
 *      - set the chip's reset input
 *
 * - void set_clock(bool val)
 *      - set the chip's clock input (unsupported: use step_clock instead)
 *
 * - void step_clock(bool val)
 *      - create one clock cycle with length 2us
 */


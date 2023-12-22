#include <Arduino.h>
#include "chip_interface.h"

void setup() {
    Serial.begin(115200);
    init_portio();

    // Step the clock a few times to get the design selected
    step_clock(10);

    // Reset the design
    set_reset(1);
    step_clock(10);
    set_reset(0);

    // Enable counting
    set_input(0, 1);

    while (true) {
        step_clock();
        delay(100);
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


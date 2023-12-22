#include <Arduino.h>
#include "chip_interface.h"

void setup() {
    Serial.begin(115200);
    init_portio();

    delay(2000);

    // Step the clock a few times to get the design selected
    step_clock(100);

    // Reset the design
    set_reset(1);
    step_clock(100);
    set_reset(0);
    step_clock(100);

    char c;
    for (int des = 0; des < 64; des++) {
        set_inputs(des, 11, 6);

        // Print the ID
        if (des < 10) Serial.print(" ");
        Serial.print(des);
        Serial.print(" ");

        for (int chr = 0; chr < 64; chr++) {
            set_inputs(chr, 5, 0);
            step_clock(10);
            c = get_outputs(7, 0);

            if (c == 0) break;
            Serial.write(c);
        }
        Serial.write('\n');
    }

    while (true) {
        set_status_led(1);
        delay(500);
        set_status_led(0);
        delay(500);
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


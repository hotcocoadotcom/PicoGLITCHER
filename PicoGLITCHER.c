#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/gpio.h"

const uint POST_BASE = 0;
const uint32_t POST_MASK = 0x000000FF;

const uint CPU_PLL_BYPASS = 8;
const uint CPU_RST = 9;

void pin_setup() {
    //For use with 1N4148 diode or 8 channel level shifter. Wire GPIO 0-7 to bits 0-7 on the motherboard.
    for (uint pin = POST_BASE; pin <= 7; pin++) {
        gpio_init(pin);
        gpio_set_dir(pin, GPIO_IN);
        gpio_pull_up(pin);
    }
}

int main() {
    stdio_init_all();
    pin_setup();

    uint8_t last_code = 0xFF;

    while (true) {
        uint8_t current_code = (uint8_t)(gpio_get_all() & POST_MASK);
        if (current_code != last_code) {
            printf("%02X\n", current_code);
            last_code = current_code;
        }
        
        tight_loop_contents();
    }
}

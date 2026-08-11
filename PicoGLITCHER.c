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
    //The order of the bits is actually reversed on the console.
    //Using the https://xenonlibrary.com/wiki/Post_Codes for wiring reference, connect GPIO 0 to bit 7, GPIO 1 to bit 6, 2 to 5, etc.
    for (uint pin = POST_BASE; pin <= 7; pin++) {
        gpio_init(pin);
        gpio_set_dir(pin, GPIO_IN);
        gpio_pull_up(pin);
    }

    //FOR USE WITH 22k OHM RESISTOR OR 3-10k OHM RESISTOR DEPENDING ON MOTHERBOARD TYPE.
    gpio_init(CPU_PLL_BYPASS);
    gpio_set_dir(CPU_PLL_BYPASS, GPIO_OUT);

    gpio_init(CPU_RST);
    gpio_set_dir(CPU_RST, GPIO_OUT);
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
        
        sleep_us(1);
    }
}

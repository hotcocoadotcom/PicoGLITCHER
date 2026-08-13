# RP2040 glitch prototype for Xbox 360 consoles.
This project is WIP. Track progress below. Currently only writing code for RGH1.2

- [ ] Wait for level shifter & other parts to arrive from AliExpress...
- [ ] Read 8-bit POST bus
- [ ] Pray that the CPU slows and console doesnt die
- [ ] Successfully pulse CPU_RST and glitch the console at least once

OPTIONAL:
- [ ] Tune timings
- [ ] Support EXT_CLK and S-RGH

CONSOLES I OWN THAT I CAN TEST THIS ON:
- [ ] Xenon
- [ ] Zephyr
- [X] Falcon
- [ ] Jasper
- [ ] Trinity
- [ ] Corona
- [ ] Winchester 👎

## Instructions (it doesn't actually work yet)
Connect GPIO 0-7 to POST bits 0-7

Wire GPIO 8 to CPU_PLL_BYPASS using either a 22k ohm (phat) or 10k ohm (slim) resistor. 
Do not skip the resistor or use a 1k ohm resistor on corona consoles like you would for RGH3, as the reason you do this is because the SMC GPIO and PLL_BYPASS both operate at 1.8v, but the pico still operates at 3.3v, making the resistor absolutely necessary.

Wire GPIO 9 to CPU_RST

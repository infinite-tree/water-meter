# Water Flow meter
This project replaces the traditional reed swith flow meter signal cable with one that is based on a continuous hall effect sensor.

## Hardware
  - Arduino Nano
  - Continuous 1.3 mV/G Analog Hall Effect sensor (we used the now obsolete A1302KUA-T)
  - 100K multi turn potentiometer
  - 100k high tollerance resistor
  - 22k high tollerance resistor
  - LED (optional)

## Wiring
Note that the Arduino Nano's analog comparator pins are D6 and D7. So in order to also read the two voltages being compared, those pins are jumpered to A0 and A1.

The ouput of the Hall Effect sensor can go straight to either A0 or A1. The potentiometer with a 22K inline resistor forms the top half (R1) of a voltage divider and goes to the other analog pin. The bottom half (R2) is the 100K resistor.

The LED output also doubles as the debounced digital output. Or this code can be folded into another project.
# Attiny turns on MAC Mini.

This is a variant of the main project which aims to be compatible with the Attiny10 microcontroller.

This was needed to be developed in Atmel Studio since the libraries that the Arduino framework adds, needs a huge amount of memory leaving only a few bytes for the firmware.
Then it was a better choice to only includes what is needed using Atmel Studio. 

# Limitations.
* It does not include an elegant way to test angles so you might need to do the calibration modifying the servoAnimationForPoweringOnThePc() fucntion.
* I had to do a crappy implementation of the PWM signal needed to control the servomotor.

# Notes:
* It is possible to program it using USB asp programmer

# References
* http://ww1.microchip.com/downloads/en/DeviceDoc/atmel-8127-avr-8-bit-microcontroller-attiny4-attiny5-attiny9-attiny10_datasheet.pdf
* http://www.technoblogy.com/show?1YQY
* https://www.youtube.com/watch?v=ra7bT74EGUs
* http://ww1.microchip.com/downloads/en/DeviceDoc/atmel-8127-avr-8-bit-microcontroller-attiny4-attiny5-attiny9-attiny10_datasheet.pdf
* https://www.pololu.com/docs/0J36/3.b
* https://www.instructables.com/Programming-Microcontrollers-With-a-USBasp-Program/
* https://startingelectronics.org/tutorials/AVR-8-microcontrollers/ATtiny2313-tutorial/P10-delay-library-function/

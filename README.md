# UNO turns on Mac Mini.
Firmware to move a servomotor which has a custom arm to press the power button of a Mac Mini. 

This project, then, is complemented with some 3D models that you can take from [here](https://github.com/jjjpolo/servoMotorClamp).

## How to test new angle values (only available for Arduino UNO)
1. Open a serial terminal (115200 baud rate)
2. Ensure that the terminal includes 'newline' character when sending data.
3. Send an integer value (ascii) between 0 and 180. Eg. 90

## How to program a Digispark attiny85
1. Install the following driver:
https://github.com/digistump/DigistumpArduino/releases/download/1.6.7/Digistump.Drivers.zip.
2. Add the following additional board (File > Preferences > Additional boards) http://digistump.com/package_digistump_index.json
3. Install the "Digistump AVR" board (Tools > Board > Board manager)
4. Choose the right Digispark board(Default – 16.5Mhz) Tools>Boards.

## Release notes
### V1.0
* Firmware compatible with Arduino UNO and Digispark attiny85 (thanks to C++ macros).
* Testing angle feature (only for Arduino UNO) by sending serial data.
* Servomotor animation at startup as a mean of calibration.
* Logging on serial monitor (only available for Arduino UNO)
* Different value setting for each type of board. 
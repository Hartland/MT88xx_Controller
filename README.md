# MT88XX Controller Library 

#### Beta stage of development


#### This project is a library for Arduino control of MT88xx series of analog switch arrays. 



### Version 0.95 Changes
MT8812 AX3 address bug has been fixed.
	 
Address pins are now individually assigned instead of
assigning a start pin. See example test program.



## Hardware/Dependencies 

There are no external software dependencies with the unmodified library. The library has been written to support as broad of a range of Arduino using base functions.
For compatibility,the base library uses digitalWrite to set control and address pins.
It has been tested successfully with the digitalWriteFast library and can be easily converted.

#### Tested to Date:
Uno

Nano

Mega2560

DUE



## Documents

Once project is closer to release, documentation will be located in the docs folder.

## Usage

See example test program.

Schematic for the test rig to be published soon.

### Basic description of test rig 
The test rig consists of 8 LEDS for the Y axis with the cathodes connected to ground. The anodes connect to Y axis pins.

For the X axis 8, 12 , or 16 LEDS are used. Anodes are connected to VCC through a current limiting resistor (300 - 470 ohms).

The anodes can be tied together as only one LED at a time will be active during normal operation. The cathodes are connected to x axis pins.

The array will connect an X and Y LED in series.

The test program will scan down the X axis while scanning the entire Y axis in between each change of the X axis.
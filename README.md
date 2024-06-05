# MT88XX Controller Library 

#### This project is a library for Arduino control of MT88xx series of analog switch arrays. 


*  Beta stage of development





### Version 0.95 Changes
* MT8812 AX3 address bug has been fixed.
	 
* Address pins are now individually assigned instead of using a start pin. Refer to the example test program for details.



## Hardware/Dependencies 

There are no external software dependencies with the unmodified library. The library has been written to support a broad range of Arduino boards using base functions. For compatibility, the base library uses digitalWrite to set control and address pins. It has been tested successfully with the digitalWriteFast library and can be easily converted if needed.

#### Tested to Date:
* Uno

* Nano

* Mega2560

* DUE



## Documents

Once project is closer to release, documentation will be located in the docs folder.

## Usage

* See example test program.

* Schematic for the test rig to be published soon.

### Basic description of test rig to use with test program

The test rig consists of the following components and connections:

* Y Axis LEDs
	*  8 LEDs
	*  Connections:
		*  Cathodes: Connected to ground.
		*  Anodes: Connected to the Y-axis pins of the MT88xx chip.

* X Axis LEDs
	* 8, 12, or 16 LEDs (depending on the configuration).
	* Connections:
		* Anodes: Connected to VCC through a current-limiting resistor 	(300-470 ohms).
		* The anodes can be tied together as only one pair of LEDs 	will be active at any given time.
		*  Cathodes: Connected to the X-axis pins of the MT88xx chip.

* Operation

 	The array will connect an X and Y LED in series.
  * The test program will:
      * Scan down the X axis.
      * For each X-axis pin, it will scan the entire Y axis.
      * This ensures that each possible X-Y LED pair is tested.


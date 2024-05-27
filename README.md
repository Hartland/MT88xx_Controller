# MT88XX Controller Library 

#### This project is a library for Arduino control of MT88xx series of analog switch arrays. 

#### This is still in the Alpha/Beta stage



## Hardware/Dependencies 

There are no external software dependencies with the unmodified library. The library has been written to support as broad of a range of Arduino using base functions.
For compatibility,The base library uses digitalWrite to set control and address pins.
It has been tested successfully with the digitalWriteFast library and can be easily converted.

#### Tested to Date:
Uno

Nano

Mega2560

DUE



## Documents

Documentation will be located in the docs folder

## Usage

Code is example of setup in a sketch. Values shown are the defualt values that the library will assume if not explictally set
Example sketch to follow soon

```
#include mt88xx //Set according to name and location of library
 mt88xx array;


void setup() {
   // Configure MT88XX control library
  array.setModel(8); // Chip model. MT8808 = 8  MT8812 = 12  MT8816 = 16
  array.setErrorLED(13, false); // Error led pin, enable/disable
  array.setControlPins(4, 2, 5, 8, 12, 11); // Data, Strobe, AY start, AX Start, AX3, Reset | Both AY and AX consist of 3 sequential pins beginning at AY & AX start. AX3 is only used for MT8812/16. 
  array.begin();
}

void loop() {
    
    SwitchAddress addr = {7, 0, true}; // Initialize addr with initial values. SwitchAddress is the strucure that defines the varible addr. {X, Y, true/false} True = Make / False = Break

    array.setSwitch(addr); // Commands switch array to make/break connection between  X and Y points.
   
    delay(1000); 
    addr.makeBreak = false; // Change only the makeBreak property for reuse
    array.setSwitch(addr);
    delay(1000);
}


/*
MIT License

Copyright (c) 2024 Hartland PC LCC
Written by: Robert VanHazinga

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <mt88xx.h>
mt88xx array;

// Using variable for setModel and loop routine
int model = 8; // Chip model. MT8808 is default. MT8808 = 8  MT8812 = 12  MT8816 = 16

void setup() {
   // Configure MT88XX control library
  array.setModel(model); // Chip model. MT8808 is default. MT8808 = 8  MT8812 = 12  MT8816 = 16
  array.setErrorLED(13, true); // Error led pin, enable/disable
  uint8_t ayPins[3] = {5, 6, 7}; // Define AY pins
  uint8_t axPins[3] = {8, 9, 10}; // Define AX pins
  array.setControlPins(3, 4, axPins, ayPins, 11, 12); // Data, Strobe, AX pins, AY pins, AX3, Reset
  array.begin();
}

void loop() {
  SwitchAddress addr = {0, 0, true}; // Initialize addr with initial values 
   array.resetArray();
  for (int x=0; x < model;x++){
    addr.ax = x;
      for (int y=0; y < 8; y++){
        addr.ay = y;
        addr.makeBreak = true;
        array.setSwitch(addr);
        delay(100); 
        addr.makeBreak = false;
        array.setSwitch(addr);
      }
    }
  }

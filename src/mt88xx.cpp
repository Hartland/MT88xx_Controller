/*
MIT License

Copyright (c) 2024 Hartland PC LLC
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

#include "mt88xx.h"

int addressMap8816[16] = {0, 1, 2, 3, 4, 5, 8, 9, 10, 11, 12, 13, 6, 7, 14, 15};

void mt88xx::resetArray() {
  digitalWrite(_resetPin, HIGH);
  digitalWrite( _strobePin, HIGH);
  digitalWrite(_resetPin, LOW);
  digitalWrite( _strobePin, LOW);
}

void mt88xx::setSwitch(const SwitchAddress& address){
  bool bit;
  int ax = address.ax; //adress.ax is copied as it may need to be modified based on model. address.ay never needs to be modified.
// Check ax address is in range by chip type. ay address range is the same for all.
if (((_model == 8 && ax < 8) || (_model == 12 && ax < 12) || (_model == 16 && ax < 16)) && address.ay < 8) { 

  //Sets make/break pin
  digitalWrite ( _dataPin, address.makeBreak);


  // MT8808 does not have the ax address logic hole and does not need to be adjusted
  // Checks if MT8812 and adjusts for address logic hole by shifting ax address values greater then 5 up 2 positions and set AX3 pin high
  if ( _model == 12 && (ax > 5) ) {
      ax +=2;
      digitalWrite(_ax3Pin,HIGH);
      }

  // Checks if MT8816 and adjusts for address logic hole by using addressMap8816 array to correct the ax address value. Sets AX3 pin state.    
  if ( _model == 16 ) {
      ax = addressMap8816[address.ax];
      digitalWrite(_ax3Pin, ax > 7 ? HIGH : LOW);
      }

  // Set address pins (AY0-AY2 & AX0-AX2) and commit all with strobe.
  // Set AY pins
  for (int i = 0; i < 3; i++) {
      bit = bitRead(address.ay, i);
      digitalWrite(_ayStartPin + i, bit);
      }   

  // Set AX pins. Local copy of address.ax is used as it may have needed modification based on model.
  for (int i = 0; i < 3; i++) {
      bit = bitRead(ax, i);
      digitalWrite(_axStartPin + i, bit);
      }

  // Strobe to commit address and make/break
  digitalWrite( _strobePin, HIGH);
  // Note that 20ns minimum strobe pulse time is required and delay will need to be added here if very fast hardware used.
  digitalWrite( _strobePin, LOW);
  }

 // If error led indication is enabled, flash led if ax or ay address is out of range for model.
else if (_errorLedEnabled) {
    digitalWrite(_errorLedPin, HIGH);
    delay(100); // Flash for 100 ms
    digitalWrite(_errorLedPin, LOW);
    } 
    
if (_model == 12 || _model == 16 ) {_ax3Pin,LOW;} //Reset AX3 pin if used based on model
}

mt88xx::mt88xx()
{
    _model = 8;  // Default to MT8808
    _errorLedEnabled = false;
    _errorLedPin = 13; // Default LED pin
    _dataPin = 4;
    _strobePin = 2;
    _ayStartPin = 5;
    _axStartPin = 8;
    _ax3Pin = 12;
    _resetPin = 11;
}


void mt88xx::setModel(uint8_t model) {
    if (model == 8 || model == 12 || model == 16) {
        _model = model;
    } else {
        _model = 8;
    }
}

void mt88xx::setErrorLED(uint8_t pin, bool enabled) {
    _errorLedPin = pin;
    _errorLedEnabled = enabled;
}

void mt88xx::setControlPins(uint8_t dataPin, uint8_t strobePin, uint8_t ayStart, uint8_t axStart, uint8_t ax3Pin, uint8_t resetPin) {
    _dataPin = dataPin;
    _strobePin = strobePin;
    _ayStartPin = ayStart;
    _axStartPin = axStart;
    _ax3Pin = ax3Pin;
    _resetPin = resetPin;
}
void mt88xx::begin() {
  // initialize the pins
  if  (_errorLedEnabled) {pinMode (_errorLedPin,OUTPUT);
      digitalWrite (_errorLedPin, LOW);}

    for ( int currentPin = _ayStartPin; currentPin <= (_ayStartPin + 3); ++currentPin) {
      pinMode(currentPin, OUTPUT);
    }
    for ( int currentPin = _axStartPin; currentPin <= (_axStartPin + 3); ++currentPin) {
      pinMode(currentPin, OUTPUT);
    }
  if (_model ==12 || _model == 16){pinMode( _ax3Pin, OUTPUT);}  // _ax3Pin (AX3) is separate as it is only used in MT8812/16
  pinMode( _strobePin, OUTPUT);  // MT88XX strobe
  pinMode( _dataPin, OUTPUT);   // MT88XX data
  pinMode( _resetPin, OUTPUT); // MT88XX reset
  resetArray();
  
}


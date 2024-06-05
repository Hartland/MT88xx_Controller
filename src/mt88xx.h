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


#ifndef mt88xx_h
#define mt88xx_h

#include "Arduino.h"

struct SwitchAddress {
    uint8_t ax;
    uint8_t ay;
    bool makeBreak;
};

class mt88xx {
public:
    mt88xx();

    void begin();
    void resetArray();
    void setSwitch(const SwitchAddress& address);
    void setModel(uint8_t model);
    void setErrorLED(uint8_t pin, bool enabled);
    void setControlPins(uint8_t dataPin, uint8_t strobePin, const uint8_t axPins[3], const uint8_t ayPins[3], uint8_t ax3Pin, uint8_t resetPin);
   
private:
    uint8_t _model;
    bool _errorLedEnabled;
    uint8_t _errorLedPin;
    uint8_t _dataPin;
    uint8_t _strobePin;
    uint8_t _axPins[3];
    uint8_t _ayPins[3];
    uint8_t _ax3Pin;
    uint8_t _resetPin;
    
};

#endif

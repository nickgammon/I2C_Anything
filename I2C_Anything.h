// Written by Nick Gammon
// May 2012
// Jan 2022 Rev by Frank Paynter to accomodate multiple I2C busses

#include <Arduino.h>
#include <Wire.h> //07/06/20 chg back for I2C hangup testing

template <typename T> unsigned int I2C_writeAnything (const T& value, void *wireObj = 0)
  {

  //01/20/22 allow use of Wire1, Wire2, etc
  TwoWire* useWire = &Wire; //default is 'original' Wire
  if (wireObj) useWire = (TwoWire*)wireObj;//use this if a non-zero addr was supplied
  const byte * p = (const byte*) &value;
    unsigned int i;
    for (i = 0; i < sizeof value; i++)
      useWire->write(*p++);

    return i;
  }  // end of I2C_writeAnything

template <typename T> unsigned int I2C_readAnything(T& value, TwoWire* wireObj = 0)
  {
  //01/20/22 allow use of Wire1, Wire2, etc
  TwoWire* useWire = &Wire; //default is 'original' Wire
  if (wireObj) useWire = (TwoWire*)wireObj;//use this if a non-zero addr was supplied

    byte * p = (byte*) &value;
    unsigned int i;
    for (i = 0; i < sizeof value; i++)
          *p++ = useWire->read();

    return i;
  }  // end of I2C_readAnything



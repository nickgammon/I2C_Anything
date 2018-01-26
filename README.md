## I2C_Anything library for Arduino

The core I2C library just sends and receives bytes. Often enough you might want to send a float, int or long type. The small I2C_Anything library helps solve that.

The library basically consists of this file: **I2C_Anything.h**

## Example of sending

For example, to send a float and long to another Arduino ...

### Master

```c++
// Written by Nick Gammon
// May 2012

#include <Wire.h>
#include <I2C_Anything.h>

const byte SLAVE_ADDRESS = 42;

void setup()
{
  Wire.begin ();
}  // end of setup

void loop()
{

 long foo = 42;

 for (float fnum = 1; fnum <= 10; fnum += 0.015)
    {
    Wire.beginTransmission (SLAVE_ADDRESS);
    I2C_writeAnything (fnum);
    I2C_writeAnything (foo++);
    Wire.endTransmission ();

    delay (200);
    }  // end of for

}  // end of loop
```

## Example of receiving

### Slave

```c++
// Written by Nick Gammon
// May 2012

#include <Wire.h>
#include <I2C_Anything.h>

const byte MY_ADDRESS = 42;

void setup()
{
  Wire.begin (MY_ADDRESS);
  Serial.begin (115200);
  Wire.onReceive (receiveEvent);
}  // end of setup

volatile boolean haveData = false;
volatile float fnum;
volatile long foo;

void loop()
{
  if (haveData)
    {
    Serial.print ("Received fnum = ");
    Serial.println (fnum);
    Serial.print ("Received foo = ");
    Serial.println (foo);
    haveData = false;
    }  // end if haveData

}  // end of loop

// called by interrupt service routine when incoming data arrives
void receiveEvent (int howMany)
 {
 if (howMany >= (sizeof fnum) + (sizeof foo))
   {
   I2C_readAnything (fnum);
   I2C_readAnything (foo);
   haveData = true;
   }  // end if have enough data
 }  // end of receiveEvent
```


---

For more information about I2C see [my page about I2C](http://www.gammon.com.au/i2c).

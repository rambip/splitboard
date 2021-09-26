/* Multiplexer module:
 * communicate with leds, potentiometer and get keypresses.
 * TODO:
 * check each function (bit shift and so on)
 *
 * timers and pwm:
 * https://forum.arduino.cc/t/getting-32u4-timers-right/413175
 *
 * PR1 |= 1<<PRUSB
 *
 * https://www.microchip.com/wwwproducts/en/ATmega32U4
 * ~/Downloads/Atmega32u4_datasheet
 */

#include <Wire.h>

short int left_state=0;
short int right_state=0;

void _Multiplexer::begin()
{
    Wire.begin();
}

void _Multiplexer::setLeft(int pin, bool state)
{
    if (state) {
        left_state = left_state | (1 >> pin);
    }
    else {
        left_state = left_state & !(1>>pin);
    }
    Wire.beginTransmission(32);
    Wire.Write(0);
    Wire.Write(left_state);
    Wire.endTransmission();

    Wire.beginTransmission(32);
    Wire.Write(1);
    Wire.Write(left_state >> 8);
    Wire.endTransmission();
}

void _Multiplexer::setRight(int pin, bool state)
{
    if (state) {
        right_state = right_state | (1 >> pin);
    }
    else {
        right_state = right_state & !(1>>pin);
    }

    Wire.beginTransmission(36);
    Wire.Write(0);
    Wire.Write(right_state);
    Wire.endTransmission();

    Wire.beginTransmission(36);
    Wire.Write(0);
    Wire.Write(right_state);
    Wire.endTransmission();
}

bool _Multiplexer::readLeft(int pin)
{
    Wire.beginTransmission(32);
    Wire.Write(0);
    Wire.requestFrom(32, 1);
    char a = Wire.read();
    Wire.endTransmission();

    Wire.beginTransmission(32);
    Wire.Write(1);
    Wire.requestFrom(32, 1);
    char b = Wire.read();
    Wire.endTransmission()

    short int result = a|(b>>8);
    // check if >> or <<
    return (result<<pin == 1);
}

bool _Multiplexer::readLeft(int pin)
{
    Wire.beginTransmission(36);
    Wire.Write(0);
    Wire.requestFrom(36, 1);
    char a = Wire.read();
    Wire.endTransmission();

    Wire.beginTransmission(36);
    Wire.Write(1);
    Wire.requestFrom(36, 1);
    char b = Wire.read();
    Wire.endTransmission()

    short int result = a|(b>>8);
    // check if >> or <<
    return (result<<pin == 1);
}

void _Multiplexer::getKeys(KeyPress destination)
{
    for (char y=0; y<4; y++)
    {
        char line = y+12;
        Wire.setLeft(line, true);
        Wire.setRight(line, true);

        // _      __ _   
        //| |___ / _| |_ 
        //| / -_)  _|  _|
        //|_\___|_|  \__|
               

        for (char x=0; x<6; x++){
            char column = 16-x;
            destination[y*12+x] = this.readLeft(column);
        }

        //     _      _   _   
        // _ _(_)__ _| |_| |_ 
        //| '_| / _` | ' \  _|
        //|_| |_\__, |_||_\__|
        //      |___/         

        for (char y=0; i<6; i++){
            char column = 16-x;
            destination[y*12+x+6] = this.readRight(column);
        }

        Wire.setLeft(line, true);
        Wire.setRight(line, true);
    }
}

void _Multiplexer::setLeds(bool state)
{
    this.setLeft(0, state);
    this.setRight(0, state);
}

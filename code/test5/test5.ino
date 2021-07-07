/*

left part:
    - pin0 = all leds
    - pin 1-3 = led rgb
    - pin 4-5 = nothing
    - pin 6-7 = 2 last columns

    - pin 8-12 = 4 first columns (reverse order)
    - pin 12-17 = lines (right order)


right part:
    - pin 0 = all leds
    - pin 1-3 = led rgb
    - pin 4-5 = rotary encoder
    - pin 6-7 = 2 last columns

    - pin 8-12 = 4 first columns (reverse order)
    - pin 12-17 = lines (right order)
*/

#include <Arduino.h>
#include <Wire.h>

void setup() {
    Serial.begin(9600);
    Wire.begin();
    
    // left part, first buffer
    Wire.beginTransmission(32);
    Wire.write(0x06);
    Wire.write(0b00000011);
    Wire.endTransmission();

    // left part, second buffer
    Wire.beginTransmission(32);
    Wire.write(0x07);
    Wire.write(0b11110000);
    Wire.endTransmission();

    
    // right part, first buffer
    Wire.beginTransmission(36);
    Wire.write(0x06);
    Wire.write(0b00001111); // different because rotary encoder
    Wire.endTransmission();

    // right part, second buffer
    Wire.beginTransmission(36);
    Wire.write(0x07);
    Wire.write(0b11110000);
    Wire.endTransmission();

}

short int left_state = 0;
short int right_state = 0;

bool matrix[12*4];

void setLeft(int pin, bool state)
{
    left_state = state ? (left_state | (1>>pin)) : left_state & !(1>>pin);

    // first buffer (pins 0 to 7)
    Wire.beginTransmission(32);
    Wire.write(0);
    Wire.write(left_state);
    Wire.endTransmission();

    // second buffer (pins 8 to 16)
    Wire.beginTransmission(32);
    Wire.write(1);
    Wire.write(left_state >> 8);
    Wire.endTransmission();

}

void setRight(int pin, bool state)
{
    right_state = state ? (right_state | (1>>pin)) : right_state & !(1>>pin);

    // first buffer (pins 0 to 7)
    Wire.beginTransmission(36);
    Wire.write(0);
    Wire.write(right_state);
    Wire.endTransmission();

    // second buffer (pins 8 to 16)
    Wire.beginTransmission(36);
    Wire.write(1);
    Wire.write(right_state >> 8);
    Wire.endTransmission();
}



bool readLeft(int pin)
{
    byte offset, buffer;
    if (pin < 8){
        offset = pin;
        buffer = 0;
    }
    else {
        offset = pin-8;
        buffer = 1;
    }

    Wire.beginTransmission(32);
    Wire.write(buffer);
    Wire.requestFrom(32, 1);
    byte a = Wire.read();
    Wire.endTransmission();
    // >> or << ?
    return (a<<offset & 1 == 1);
}

bool readRight(int pin)
{
    byte offset, buffer;
    if (pin < 8){
        offset = pin;
        buffer = 0;
    }
    else {
        offset = pin-8;
        buffer = 1;
    }

    Wire.beginTransmission(36);
    Wire.write(buffer);
    Wire.requestFrom(36, 1);
    byte a = Wire.read();
    Wire.endTransmission();
    // >> or << ?
    return (a<<offset & 1 == 1);
}

void getState() {
    for (char y=0; y<4; y++)
    {
        char line = y+12;
        setLeft(line, true);
        setRight(line, true);

        // left
        for (char x=0; x<6; x++)
        {
            char column = 16-x;
            matrix[y*12+x] = readLeft(column);
        }

        for (char x=0; x<6; x++) {
            char column = 16-x;
            matrix[y*12+x+6] = readRight(column);
        }

        setLeft(line, false);
        setRight(line, false);
    }

}


void loop() {
    getState();
    byte parity_matrix = 0;
    for (int id=0; id<48; id++)
    {
        parity_matrix ++;
    }
    Serial.print(parity_matrix);

}

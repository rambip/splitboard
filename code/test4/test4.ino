/*

Turn on leds and give buffer state (only left part)

00000001
-> this will turn on the port num. 0
*/

/*

left part:
    - pin0 = all leds          [out]
    - pin 1-3 = led rgb        [out]
    - pin 4-5 = nothing
    - pin 6-7 = 2 last columns [out]

    - pin 8-12 = 4 first columns (reverse order) [out]
    - pin 12-17 = lines (right order) [in]


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

#define LEFT_I2C  0b00100100
#define RIGHT_I2C 0b00100000

byte matrix[12*4];


void setup() {
    Serial.begin(9600);
    Wire.begin();
    delay(50);

    Wire.beginTransmission(LEFT_I2C);
    Wire.write(0x06);
    Wire.write(0b11000000);
    Wire.endTransmission();

    Wire.beginTransmission(LEFT_I2C);
    Wire.write(0x07);
    Wire.write(0b00001111); // 0 = output, 1 = input
    Wire.endTransmission();

    Wire.beginTransmission(RIGHT_I2C);
    Wire.write(0x06);
    Wire.write(0b11000000);
    Wire.endTransmission();

    Wire.beginTransmission(RIGHT_I2C);
    Wire.write(0x07);
    Wire.write(0b00001111);
    Wire.endTransmission();
}







byte getLine(int adress, uint8_t line) // return the byte 00abcdef
{
    // set the line to high
    Wire.beginTransmission(adress);
    Wire.write(0x03);
    uint8_t pin = 4 + line;
    Wire.write(~ (1<<pin));
    Wire.endTransmission();

    // request state of 2 buffers
    Wire.beginTransmission(adress);
    Wire.write(0x00);
    Wire.endTransmission();

    Wire.requestFrom(adress, 1);
    byte buff0 = Wire.read();
    Wire.endTransmission();

    Wire.beginTransmission(adress);
    Wire.write(0x01);
    Wire.endTransmission();

    Wire.requestFrom(adress, 1);
    byte buff1 = Wire.read();
    Wire.endTransmission();


    // put together the 2 outputs:
    // return value = byte between 0b000000 and 0b111111

    // we want = abdcef (state of keyboard on that line)
    // buff0 = efxxxxxx
    // buff1 = xxxxabcd
    return ~((buff0 & 0b11000000) >> 6 | (buff1 & 0b00001111) << 2);
}



void loop() {
    byte left = getLine(LEFT_I2C, 2);
    byte right = getLine(RIGHT_I2C, 2);

    Serial.print(left, BIN);
    Serial.print("\t");
    Serial.println(right, BIN);
}

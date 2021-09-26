
/*
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
- pin 0 = all leds [out]
- pin 1-3 = led rgb [out]
- pin 4-5 = rotary encoder [in ?]
- pin 6-7 = 2 last columns [out]

- pin 8-12 = 4 first columns (reverse order) [out]
- pin 12-17 = lines (right order) [in]
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

// 0 = output, 1 = input
Wire.beginTransmission(RIGHT_I2C);
Wire.write(0x06);
Wire.write(0b11000000);
Wire.endTransmission();

Wire.beginTransmission(RIGHT_I2C);
Wire.write(0x07);
Wire.write(0b00001111);
Wire.endTransmission();

// TODO: vérifier l'emplacement du rotary encoder
// récupérer les impulsions, check quelle fréquence il faut
// s'en servir pour passer de azerty -> qwerty -> [pad numérique ?]
}










void loop() {
    Wire.beginTransmission(RIGHT_I2C);
    Wire.write(0x00);
    Wire.endTransmission();

    Wire.requestFrom(RIGHT_I2C, 1);
    byte buff = Wire.read();
    Wire.endTransmission();

    byte s1 = (~buff & 0b00100000) != 0;
    byte s2 = (~buff & 0b01000000) != 0;

    if (s1 || s2) { 
        Serial.println(s1, BIN);
    }
}

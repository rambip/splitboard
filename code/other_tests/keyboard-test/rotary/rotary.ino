#include <Arduino.h>
#include <Wire.h>


#define LEFT_I2C  0b00100100
#define RIGHT_I2C 0b00100000


void setup() {
    Wire.begin();
    Wire.beginTransmission(RIGHT_I2C);
    Wire.write(0x07);
    Wire.write(0b00001100);
    Wire.endTransmission();
}

byte buff;
byte last_buff;

void loop() {
    Wire.beginTransmission(RIGHT_I2C);
    Wire.write(0x00);
    Wire.requestFrom(RIGHT_I2C, 1);
    buff = Wire.read();
    Wire.endTransmission();
    if (buff != last_buff){
        Serial.println((buff >> 4) & 0b11, BIN);
    }
    last_buff = buff;
}

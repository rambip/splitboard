/*

Turn on leds and give buffer state (only right part)

*/

#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

void setup() {
    Serial.begin(9600);
    Wire.begin();
    delay(50);

    Wire.beginTransmission(36);
    Wire.write(0x06);
    Wire.write(0b00000011);
    Wire.endTransmission();

    Wire.beginTransmission(36);
    Wire.write(0x07);
    Wire.write(0b11110000);
    Wire.endTransmission();

}

byte result;

void loop() {
    Wire.beginTransmission(36);
    Wire.write(0);

    // turn on leds
    Wire.beginTransmission(36);
    Wire.write(0);
    Wire.write(0b10000000);
    Wire.endTransmission();

    // turn on lines
    Wire.beginTransmission(36);
    Wire.write(1);
    Wire.write(0b00001111);
    Wire.endTransmission();

    // read state
    Wire.beginTransmission(36);
    Wire.write(0);
    Wire.requestFrom(32, 1);
    result = Wire.read();
    Serial.print(F("in buffer 0 there is:  "));
    Serial.println(result);
    Serial.println();
    Wire.endTransmission();

    Wire.beginTransmission(36);
    Wire.write(0);
    Wire.requestFrom(32, 1);
    result = Wire.read();
    Serial.print(F("in buffer 1 there is:  "));
    Serial.println(result);
    Wire.endTransmission();
}

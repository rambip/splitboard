/*

Turn on leds and give buffer state (only left part)

00000001
-> this will turn on the port num. 0
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
    Wire.write(0b11000000);
    Wire.endTransmission();

    Wire.beginTransmission(36);
    Wire.write(0x07);
    Wire.write(0b00001111);
    Wire.endTransmission();

    Wire.beginTransmission(32);
    Wire.write(0x06);
    Wire.write(0b11000000);
    Wire.endTransmission();

    Wire.beginTransmission(32);
    Wire.write(0x07);
    Wire.write(0b00001111);
    Wire.endTransmission();
}

short int left_state = 0;
short int right_state = 0;

byte result;
unsigned long global_count = 0;

void loop() {
    global_count++;

    // turn on leds
    if (global_count % 2000 < 1000) {
        Wire.beginTransmission(32);
        Wire.write(0x02);
        Wire.write(0b0000000);
        Wire.endTransmission();

        Wire.beginTransmission(36);
        Wire.write(0x02);
        Wire.write(0b0000001);
        Wire.endTransmission();
    }
    else {
        Wire.beginTransmission(32);
        Wire.write(0x02);
        Wire.write(0b11111111);
        Wire.endTransmission();

        Wire.beginTransmission(36);
        Wire.write(0x02);
        Wire.write(0b00000000);
        Wire.endTransmission();
    }

    // turn on lines
    Wire.beginTransmission(36);
    Wire.write(0x03);
    Wire.write(0b11110000);
    Wire.endTransmission();

    // read state
    //Wire.beginTransmission(36);
    //Wire.write(0);
    //Wire.requestFrom(36, 1);
    //result = Wire.read();
    //Serial.print(F("in buffer 0 there is:  "));
    //Serial.println(result);
    //Serial.println();
    //Wire.endTransmission();

    //Wire.beginTransmission(36);
    //Wire.write(0);
    //Wire.requestFrom(36, 1);
    //result = Wire.read();
    //Serial.print(F("in buffer 1 there is:  "));
    //Serial.println(result);
    //Wire.endTransmission();
}

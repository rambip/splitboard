#include "Keyboard_get.h"

bool matrix[48];

void setup_i2c() {
    Wire.begin();

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

void read_keys() {
    for (int y=0; y<4; y++)
    {
        byte left = getLine(LEFT_I2C, y);
        byte right = getLine(RIGHT_I2C, y);

        for (int x=0; x<6; x++)
        {
            bool pressed = (left >> (5-x)) & 1;
            matrix[y*12+x] = pressed;
        }

        for (int x=0; x<6; x++)
        {
            bool pressed = (right >> (5-x)) & 1;
            matrix[y*12+6+x] = pressed;
        }
    }
}

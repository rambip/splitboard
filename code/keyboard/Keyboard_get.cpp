#include "Keyboard_get.h"

bool matrix[48];
RotaryEncoderSignal rotary_encoder;
bool rotary_last_on_on;

/*
 * MULTIPLEXER:
 * our multiplexers have 2 buffers, representing the 16 pins.
 * each can be input/output.
 * you can define each pin as output or input.
 *
 * to do something:
 * - you first send the adress (Wire.beginTransmission(adress))
 * - then you send the "command" byte (0x06 for define first buffer, 0x07 for define second buffer, 0x02/3 to write, 0x00/1 to read)
 * - you send the "data" byte, representing the bits that you want
 * - then you endTransmission
 *
 */

void setup_i2c() {
    Wire.begin();

    // define inputs/outputs pins in the left multiplexer
    Wire.beginTransmission(LEFT_I2C);
    Wire.write(0x06);
    Wire.write(0b11000000);
    Wire.endTransmission();

    Wire.beginTransmission(LEFT_I2C);
    Wire.write(0x07);
    Wire.write(0b00001111); // 0 = output, 1 = input
    Wire.endTransmission();

    // define inputs/outputs pins in the right multiplexer
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
    // set the requested line to high,
    // everything else to low
    Wire.beginTransmission(adress);
    Wire.write(0x03);
    byte pin = 4 + line;
    Wire.write(~ (1<<pin));
    Wire.endTransmission();

    // request state of buffer 1
    Wire.beginTransmission(adress);
    Wire.write(0x00);
    Wire.endTransmission();

    Wire.requestFrom(adress, 1);
    byte buff0 = Wire.read();
    Wire.endTransmission();

    // request state of buffer 2
    Wire.beginTransmission(adress);
    Wire.write(0x01);
    Wire.endTransmission();

    Wire.requestFrom(adress, 1);
    byte buff1 = Wire.read();
    Wire.endTransmission();


    if (adress == RIGHT_I2C) {
        // dirty optimization: look if there is a rotary_encoder signal
        bool s1 = (~buff0 & 0b00100000) != 0;
        bool s2 = (~buff0 & 0b00010000) != 0;

        if (s1 && !s2 && rotary_last_on_on) {
            // on-on -> on-off: right rotation
            rotary_encoder = RE1;
        }
        else if (s2 && !s1 && rotary_last_on_on) {
            // on-on -> off-on : left rotation
            rotary_encoder = RE2;
        }
        rotary_last_on_on = s1 && s2;
    }

    // put together the 2 outputs:
    // return value = byte between 0b000000 and 0b111111

    // we want = abdcef (state of keyboard on that line)
    // buff0 = efxxxxxx
    // buff1 = xxxxabcd
    return ~((buff0 & 0b11000000) >> 6 | (buff1 & 0b00001111) << 2);
}

int read_keys() {
    int total_keys_pressed = 0; 

    // for each line, get the data from the 2 sides
    for (int y=0; y<4; y++)
    {
        byte left = getLine(LEFT_I2C, y);
        byte right = getLine(RIGHT_I2C, y);

        // then combine them to fill the `matrix` table
        for (int x=0; x<6; x++)
        {
            bool pressed = (left >> (5-x)) & 1;
            matrix[y*12+x] = pressed;
            total_keys_pressed += pressed;
        }

        for (int x=0; x<6; x++)
        {
            bool pressed = (right >> (5-x)) & 1;
            matrix[y*12+6+x] = pressed;
            total_keys_pressed += pressed;
        }
    }
    return total_keys_pressed;
}

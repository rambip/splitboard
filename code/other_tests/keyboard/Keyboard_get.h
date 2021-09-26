#ifndef KEYBOARD_GET_LIB
#define KEYBOARD_GET_LIB

#include <Wire.h>
#include <Arduino.h>

#define LEFT_I2C  0b00100100
#define RIGHT_I2C 0b00100000


extern bool matrix[12*4];

void setup_i2c();
byte getLine(int adress, uint8_t line); 
void read_keys() ;

#endif

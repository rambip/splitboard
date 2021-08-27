#pragma once

// libraries for I2C protocol 
#include <Wire.h>

#define LEFT_I2C  0b00100100 // I2C address of the left multiplexer
#define RIGHT_I2C 0b00100000 // I2C address of the right multiplexer


#define byte unsigned char

// table of booleans storing the state of the keys
extern bool matrix[12*4];

void setup_i2c();
byte getLine(int adress, uint8_t line); 
int read_keys() ;

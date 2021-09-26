#ifndef KEYBOARD_BLE_LIB
#define KEYBOARD_BLE_LIB


#include <Adafruit_BluefruitLE_SPI.h>

void setup_ble();
void send_keys_ble(byte report[8]);


#endif

/********************************************************************
           _ _ _   _                         _ 
 ___ _ __ | (_) |_| |__   ___   __ _ _ __ __| |
/ __| '_ \| | | __| '_ \ / _ \ / _` | '__/ _` |
\__ \ |_) | | | |_| |_) | (_) | (_| | | | (_| |
|___/ .__/|_|_|\__|_.__/ \___/ \__,_|_|  \__,_|
    |_|                                        

amazing arduino code to emulate a keyboard with adafruit feather


# ressources:

https://learn.adafruit.com/introducing-adafruit-ble-bluetooth-low-energy-friend/ble-services
https://wiki.osdev.org/USB_Human_Interface_Devices
https://www.microchip.com/forums/m116779.aspx
https://eleccelerator.com/tutorial-about-usb-hid-report-descriptors/


# how that works:

## hid protocol for keyboards:

1 report = 8 bytes

  01000001   00000000   00000100 00000010 00000000 00000000 00000000 00000000 
 Modifiers    empty      key 1     key 2    key 3    key 4    key 5    key 6
  keys 

-> up to 6 keys = 6-keys rollover

if 3 keys are currently pressed, the bytes 2, 3 and 4 are set, in any order

## Modifier Keys:

bit 0 = Left ctrl
bit 1 = Left shift
bit 2 = Left Alt
bit 3 = Left super/windows
bit 4 = Right ctrl
bit 5 = Right shift
bit 6 = Right Alt
bit 7 = Right super/windows



# I2C multiplexer:

# i2c adafruit:
- sda = 2
- scl = 3

adafruit = master
2 slaves: right multiplexer (adress 01000100 = 36)
          left multiplexer  (adress 01000000 = 32)

to write, send 2 bytes:
- register adress (0 to 15)
- data -> 0 or 1


*********************************************************************/
#include <Arduino.h>


// ble module
#include <Adafruit_BluefruitLE_SPI.h>


// Serial port
#include <SoftwareSerial.h>

// hid specification
#include <HID.h>

// i2c
#include <Wire.h>

#include "Emitter.h"
// usb hid descriptor to send to enable connexion

static const uint8_t _hidReportDescriptor[] PROGMEM = {

  //  Keyboard
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)  // 47
    0x09, 0x06,                    // USAGE (Keyboard)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x85, 0x02,                    //   REPORT_ID (2)
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
   
  0x19, 0xe0,                    //   USAGE_MINIMUM (Keyboard LeftControl)
    0x29, 0xe7,                    //   USAGE_MAXIMUM (Keyboard Right GUI)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
    0x75, 0x01,                    //   REPORT_SIZE (1)
    
  0x95, 0x08,                    //   REPORT_COUNT (8)
    0x81, 0x02,                    //   INPUT (Data,Var,Abs)
    0x95, 0x01,                    //   REPORT_COUNT (1)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x81, 0x03,                    //   INPUT (Cnst,Var,Abs)
    
  0x95, 0x06,                    //   REPORT_COUNT (6)
    0x75, 0x08,                    //   REPORT_SIZE (8)
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
    0x25, 0x73,                    //   LOGICAL_MAXIMUM (115)
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
    
  0x19, 0x00,                    //   USAGE_MINIMUM (Reserved (no event indicated))
    0x29, 0x73,                    //   USAGE_MAXIMUM (Keyboard Application)
    0x81, 0x00,                    //   INPUT (Data,Ary,Abs)
    0xc0,                          // END_COLLECTION
};




// 8, 7, 4 = pins of ble modules
Adafruit_BluefruitLE_SPI ble(8, 7, 4);

int global_counter = 0;

void setup(void)
{
        //  _     _     _ 
        // | |__ (_) __| |
        // | '_ \| |/ _` |
        // | | | | | (_| |
        // |_| |_|_|\__,_|


        // wtf ???
	static HIDSubDescriptor node(_hidReportDescriptor, sizeof(_hidReportDescriptor));
	HID().AppendDescriptor(&node);
               
        //  _     _      
        // | |__ | | ___ 
        // | '_ \| |/ _ \
        // | |_) | |  __/
        // |_.__/|_|\___|
              
        while (!Serial);
        delay(300);
        Serial.println(F("Amazing keyboard"));
        Serial.println(F("----------------"));


        ble.begin();
        ble.echo(false); 

        bool no_error = true;

        // set name and hid class, enable bleKeyboard
        no_error |= ble.sendCommandCheckOK(F( "AT+GAPDEVNAME=Splitboard"));

        //no_error |= ble.sendCommandCheckOK(F( "AT+BleHIDEn=On" ));
        no_error |= ble.sendCommandCheckOK(F( "AT+BleKeyboardEn=On"  ));

        // reset (add or remove service requires a reset)
        no_error |= ble.reset();

        if (no_error) {
                Serial.println(F("keyboard enabled without bug"));
        }
        else {
                Serial.println(F("Could not enable Keyboard"));
                while (1);
        }

        //  ___ ____   ____ 
        // |_ _|___ \ / ___|
        //  | |  __) | |    
        //  | | / __/| |___ 
        // |___|_____|\____|
                 
        Wire.begin();
}


void loop(void)
{
        // check
        if (global_counter%10000 == 0) {
                Serial.println(F("I'm working !"));
        }
        global_counter ++;


        // getinput
        
        // ble.print("AT+BleKeyboardCode=");
        // ble.println(keys);
        // ble.waitForOk()


        // HID().SendReport(2, keys, sizeof(keystruct))


        // Wire.beginTransmission(0) -> partie de droite
        // Wire.beginTransmission(4) -> partie de gauche
        // (à vérifier)
        // Wire.send();
        // Wire.recieve(); ?


}

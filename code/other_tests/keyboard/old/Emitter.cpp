#include "Emitter.h"
#include <HID.h>

Adafruit_BluefruitLE_SPI ble(8, 7, 4);

bool _Ble_keyboard::begin(void)
{
    ble.begin();
    ble.echo(false); 

    bool no_error = true;

    // set name and hid class, enable bleKeyboard
    no_error |= ble.sendCommandCheckOK(F( "AT+GAPDEVNAME=Splitboard"));

    //no_error |= ble.sendCommandCheckOK(F( "AT+BleHIDEn=On" ));
    no_error |= ble.sendCommandCheckOK(F( "AT+BleKeyboardEn=On"  ));

    // reset (add or remove service requires a reset)
    no_error |= ble.reset();

    return no_error;
}

_Ble_keyboard::_Ble_keyboard() { }

void _Ble_keyboard::send(Modifiers mod, Keys keys)
{
    ble.print("AT+BleKeyboardCode=");
    ble.print(mod);
    for (int i=0; i<6; i++) {
        ble.print(keys[i]);
    }
    ble.println();
}




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

_Usb_keyboard::_Usb_keyboard() {};

void _Usb_keyboard::begin(void){
    static HIDSubDescriptor node(_hidReportDescriptor, sizeof(_hidReportDescriptor));
    HID().AppendDescriptor(&node);
}

void _Usb_keyboard::send(Modifiers mod, Keys keys){
    //  id = 2 ?
    char* report;
    report[0] = mod;
    report[1] = 0;
    for (int i=2; i<8; i++) 
        report[i] = keys[i];

    HID().SendReport(2, report, 8*sizeof(char));
}

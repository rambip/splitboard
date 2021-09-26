#ifndef KEYBOARD_SEND_LIB
#define KEYBOARD_SEND_LIB

#include <HID.h>
#include "layout.h"

#define SEND_KEYS(x) HID().SendReport(2, x, 8)

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



void setup_hid();


const byte _dead_grave_keys[8] = {
    0b01000000, // right alt
    0x0,
    0x25, // 7
    0, 0, 0, 0, 0,
};

const byte _dead_circumflex_keys[8] = {
    0b00000000, // left shift
    0x0,
    0x2f, // [ on qwerty
    0, 0, 0, 0, 0,
};

const byte _dead_diaeresis_keys[8] = {
    0b00000010, // left shift
    0x0,
    0x2f, // [ on qwerty
    0, 0, 0, 0, 0,
};

const byte _caps_lock_keys[8] = {
    0b00000000,
    0x0,
    0x39,
    0, 0, 0, 0, 0,
};

const byte _space_keys[8] = {
    0b00000000,
    0x0,
    0x2c,
    0, 0, 0, 0, 0,
};

const byte _release_keys[8] = {
    0, 0, 0, 0, 0, 0, 0, 0,
};


// send ascii char (use to send text)

void send_char(unsigned char k, bool force_rep=false);

//template <class T> // char* in ram or in flash
//void send_string(T* adress);


void char_to_report(unsigned char k, byte report[8]);
void layer_to_report(char* layout_for_layer, byte report[8]);
void modifiers_to_report(bool ctrl, bool shift, bool alt, bool super, byte report[8]);

#endif

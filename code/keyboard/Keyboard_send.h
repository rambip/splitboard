#include <HID.h>
#include "OS_layouts.h"
#include "Keyboard_get.h" // to get the global variable matrix
#include "config.h" // to know if OS defined with azerty or qwerty

// send report to usb
#define SEND_KEYS(x) HID().SendReport(2, x, 8)

#ifdef AZERTY
#define OS_LAYOUT_MAP _azerty_map
#endif

#ifdef QWERTY
#define OS_LAYOUT_MAP _qwerty_map
#endif


static const uint8_t _hidReportDescriptor[] PROGMEM = {

  //  Define device as usb keyboard
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


extern const byte _release_keys[8];


void setup_hid();

void char_to_report(unsigned char k, byte report[8]);
void layer_to_report(char* layout_for_layer, byte report[8]);
void modifiers_to_report(bool ctrl, bool shift, bool alt, bool super, byte report[8]);

// send a string with key emulation
template <class T> // string in ram or in flash
void send_string(T* adress);

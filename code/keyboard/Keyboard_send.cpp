#include "Keyboard_send.h"
#include "OS_layouts.h"


uint8_t current_keymap = 0;

void setup_hid(){
    static HIDSubDescriptor node(_hidReportDescriptor, sizeof(_hidReportDescriptor));
    HID().AppendDescriptor(&node);
}


void send_keys(byte report[8]) {
    HID().SendReport(2, report, 8);
}


short get_key(unsigned char k) {
    short* keymap = KEYMAPS[current_keymap];
    return pgm_read_word(&keymap[k]);
}


void char_to_report(unsigned char k, byte report[8]) {
    // fill the report for the usb with the right keys to send the character
    short code = get_key(k);

    if (code & 0x0f00)
    {
        // char that need combinaison of keys
        // TODO: fix ?
        return;
    }

    byte scancode = code%0x100;

    byte shift = (code & SHIFT) != 0;
    byte altgr = (code & ALTGR) != 0;

    // modifiers for current key
    report[0] |= (shift << 1);
    report[0] |= (altgr << 6);

    for (int i=2; i<8; i++) {
        // append scancode to list of 6 scancodes
        if (report[i] == 0) {
            report[i] = scancode;
            break;
        }
    }
}


void layer_to_report(char* layout_for_layer, byte report[8]) {
    // for each key in the "layer" keys
    for (int i=0; i<36; i++) {
        if (matrix[i]) {
            // if pressed, send corresponding char
            matrix[i] = false;
            unsigned char k = pgm_read_byte(&layout_for_layer[i]);
            char_to_report(k, report);
        }
    }
}


void modifiers_to_report(bool ctrl, bool shift, bool alt, bool super, byte report[8]) {
    byte c = ctrl;
    byte s = shift;
    byte a = alt;
    byte sup = super;
    report[0] |= (c << 0) | (s << 1) | (a << 2) | (sup << 3);
}




/*               _   _           _   
 ___ ___ _ _  __| | | |_ _____ _| |_ 
(_-</ -_) ' \/ _` | |  _/ -_) \ /  _|
/__/\___|_||_\__,_|  \__\___/_\_\\__|
*/
                                     
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



template <class T> // char* in ram or in flash
void send_string(T* adress) {
    String str = String(adress); // attention pour les trop grosses strings
    for (int i=0; str[i]; i++)
    {
        short code = get_key(str[i]);

        // code on 16 bits.
        // - 4 first bits = modifiers (shift, altgr)
        // - 4 next bits = dead keys
        // - 8 next bits = scancode to send

        switch (code & 0x0f00)
        {
            // char need combination of keys
            case DEAD_GRAVE:
                send_keys(_dead_grave_keys);
                break;
            case DEAD_CIRCUMFLEX:
                send_keys(_dead_circumflex_keys);
                break;
            case DEAD_DIAERESIS:
                send_keys(_dead_diaeresis_keys);
                break;
            case LOCK:
                send_keys(_caps_lock_keys);
                break;
        }

        byte scancode = code%0x100;

        // create empty report
        byte keys[8] = {0, 0, 0, 0, 0, 0, 0, 0};


        byte shift = (code & SHIFT) == SHIFT;
        byte altgr = (code & ALTGR) == ALTGR;

        // modifiers for current key
        keys[0] = (shift << 1) | (altgr << 6);
        keys[2] = scancode;

        send_keys(keys);

        if ((code & 0x0f00) == LOCK){
            send_keys(_caps_lock_keys); // turn off capslock
        }


        if (code & SPACE){ send_keys(_space_keys); }

        // TODO: do same for ble
        // realease only if needed ?
        send_keys(_release_keys);
    }
}

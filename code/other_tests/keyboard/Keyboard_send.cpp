#include "Keyboard_send.h"
#include "Keyboard_get.h" // to get the global variable matrix

char last_scancode;

void setup_hid(){
    static HIDSubDescriptor node(_hidReportDescriptor, sizeof(_hidReportDescriptor));
    HID().AppendDescriptor(&node);
}


void send_char(unsigned char k, bool force_rep=false)
{
    short code = pgm_read_word(&_azerty_map[k]);

    // code on 16 bits.
    // - 4 first bits = modifiers (shift, altgr)
    // - 4 next bits = dead keys
    // - 8 next bits = scancode to send

    switch (code & 0x0f00)
    {
        case DEAD_GRAVE:
            SEND_KEYS(_dead_grave_keys);
            break;
        case DEAD_CIRCUMFLEX:
            SEND_KEYS(_dead_circumflex_keys);
            break;
        case DEAD_DIAERESIS:
            SEND_KEYS(_dead_diaeresis_keys);
            break;
        case LOCK:
            SEND_KEYS(_caps_lock_keys);
            break;
    }

    byte scancode = code%0x100;
    if (force_rep && scancode == last_scancode)
        SEND_KEYS(_release_keys);
    

    // create empty report
    byte keys[8] = {0, 0, 0, 0, 0, 0, 0, 0};


    byte shift = (code & SHIFT) == SHIFT;
    byte altgr = (code & ALTGR) == ALTGR;

    // modifiers for current key
    keys[0] = (shift << 1) | (altgr << 6);
    keys[2] = scancode;

    SEND_KEYS(keys);

    if ((code & 0x0f00) == LOCK){
        SEND_KEYS(_caps_lock_keys); // turn off capslock
    }


    if (code & SPACE){
        SEND_KEYS(_space_keys);
        // release everything to count the following space.
        SEND_KEYS(_release_keys);
    }
    last_scancode = scancode;
}



template <class T> // char* in ram or in flash
void send_string(T* adress) {
    String str = String(adress); // attention pour les trop grosses strings
    for (int i=0; str[i]; i++)
    {
        send_char(str[i], true);
    }
}



void char_to_report(unsigned char k, byte report[8]) {

    short code = pgm_read_word(&_azerty_map[k]);

    if (code & 0x0f00)
    {
        // char that need combinaison of keys
        return;
    }
    byte scancode = code%0x100;

    byte shift = (code & SHIFT) == SHIFT;
    byte altgr = (code & ALTGR) == ALTGR;

    // modifiers for current key
    report[0] |= (shift << 1);
    report[0] |= (altgr << 6);

    for (int i=2; i<8; i++) {
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
            char_to_report(pgm_read_byte(&layout_for_layer[i]), report);
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

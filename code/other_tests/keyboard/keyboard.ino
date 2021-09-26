#include <Arduino.h>

#include "Keyboard_send.h"
#include "Keyboard_get.h"
#include "Keyboard_ble.h"
#include "config.h"

void setup()
{
    Serial.begin(9600);
    setup_hid();
    setup_i2c();
    setup_ble();
}

void loop()
{
    read_keys();

    byte hid_report[8] = {0, 0, 0, 0, 0, 0, 0, 0};

    // check if "change layer" key is pressed.
    // if true, look at the keys in the layer
    if (matrix[SYMB_LAYER]) {
        matrix[SYMB_LAYER] = false;
        layer_to_report(_symb_layer, hid_report);
    }

    if (matrix[NUM_LAYER]) {
        matrix[NUM_LAYER] = false;
        layer_to_report(_num_layer, hid_report);
    }

    if (matrix[SHIFT_LAYER]) {
        matrix[SHIFT_LAYER] = false;
        layer_to_report(_shift_layer, hid_report);
    }

    // TODO: multimedia layout, arrows


    // if no layer key pressed, send chars from the default layout
    layer_to_report(_base_layer, hid_report);

    modifiers_to_report(
       matrix[MODIFIER_CTRL],
       false, // no shift: shift is a layering key
       matrix[MODIFIER_ALT],
       matrix[MODIFIER_SUPER],
       hid_report
    );

    if (matrix[SPACE]){ // Space
        char_to_report(' ', hid_report);
    }

    SEND_KEYS(hid_report);
    // TODO: debug
    send_keys_ble(hid_report);
}

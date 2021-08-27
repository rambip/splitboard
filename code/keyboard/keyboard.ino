#include <Arduino.h>

#include "config.h"

#include "Keyboard_get.h"
#include "Keyboard_send.h"
#include "Keyboard_ble.h"

void setup()
{
    Serial.begin(9600);
    setup_hid();
    setup_i2c();
    setup_ble();
}

bool last_time_layer_key = false;

void loop()
{
    // store every key-press detected in the "matrix" table
    int n_keys_pressed = read_keys();

    // look if layer key pressed (bottom keys)
    bool layer_key = matrix[SYMB_LAYER] || matrix[NUM_LAYER] || matrix[SHIFT_LAYER]
                     || matrix[FUNC_LAYER] || matrix[MM_LAYER];

    if ( n_keys_pressed > 0 && last_time_layer_key && !layer_key) {
        // if I just released a layer key, I wait until all keys are released.
        // Otherwise when I release a layer key, the symbol from the base layer
        // could be treagered.
        send_keys(_release_keys);
        send_keys_ble(_release_keys);
        while (n_keys_pressed > 0) {
            n_keys_pressed = read_keys();
        }
        // restart in a normal state.
        last_time_layer_key = false;
        return;
    }

    // update last layer key
    last_time_layer_key = layer_key;

    // empty usb-hid report that we will send to the OS
    byte hid_report[8] = {0, 0, 0, 0, 0, 0, 0, 0};

    // space is a special char: it is the only key that is not in the "layers"
    if (matrix[SPACE]){ // Space
        if (matrix[SHIFT_LAYER]) char_to_report('_', hid_report);
        else                     char_to_report(' ', hid_report);
    }

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

    if (matrix[FUNC_LAYER]) {
        matrix[FUNC_LAYER] = false;
        layer_to_report(_func_layer, hid_report);
    }

    // if no layer key pressed, send chars from the default layout
    layer_to_report(_base_layer, hid_report);

    // send additional modifiers (alt, super, ctrl)
    modifiers_to_report(
       matrix[MODIFIER_CTRL],
       false, // no shift: shift is a layering key now
       matrix[MODIFIER_ALT],
       matrix[MODIFIER_SUPER],
       hid_report
    );

    // send the report via usb
    send_keys(hid_report);
    send_keys_ble(hid_report);
}

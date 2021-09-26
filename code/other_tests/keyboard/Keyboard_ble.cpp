#include "Keyboard_ble.h"

Adafruit_BluefruitLE_SPI ble(8, 7, 4);

void setup_ble() {
    ble.begin();
    ble.echo(false);
    bool no_error = true;

    no_error |= ble.sendCommandCheckOK(F( "AT+GAPDEVNAME=Splitboard"));

    no_error |= ble.sendCommandCheckOK(F( "AT+BLEHIDEN=1" ));
    no_error |= ble.sendCommandCheckOK(F( "AT+BleKeyboardEn=1"  ));

    // reset (add or remove service requires a reset)
    //no_error |= ble.reset();
}

//byte last_scancode_1 = 0;

void send_keys_ble(byte report[8]) {
    //if (report[2] == last_scancode_1) return;

    ble.print("AT+BLEKEYBOARDCODE=");
    Serial.print("AT+BLEKEYBOARDCODE=");
    for (int i=0; i<5; i++){
        ble.print(report[i]/16, HEX);
        ble.print(report[i]%16, HEX);
        Serial.print(report[i]/16, HEX);
        Serial.print(report[i]%16, HEX);

        if (i < 4) {
            Serial.print("-");
            ble.print("-");
        }
    }

    //ble.println("AT+BLEKEYBOARDCODE=00-00");
    Serial.println();
    ble.println();

    if (!ble.waitForOK()) {
        Serial.println("erreur !!!");
    }

    //last_scancode_1 = report[2];
}

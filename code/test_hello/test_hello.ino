#include <Arduino.h>
#include <Adafruit_BluefruitLE_SPI.h>

#include <SoftwareSerial.h>
Adafruit_BluefruitLE_SPI ble(8, 7, 4);

long int global_counter;

void setup() {
    global_counter = 0;
    Serial.begin(9600);
    delay(300);
    Serial.println(F("test 1:"));
    ble.begin();
    ble.echo(false);


    bool no_error = true;

    // set name and hid class, enable bleKeyboard
    no_error |= ble.sendCommandCheckOK(F( "AT+GAPDEVNAME=Splitboard2"));

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

}

void loop() {
    if (global_counter%10000 == 0) {
        Serial.println(F("port serie: ok"));
    }
    if (global_counter%2000 < 1000) {
        digitalWrite(13, HIGH);
    }
    else
    {
        digitalWrite(13, LOW);
    }

    global_counter ++;
}

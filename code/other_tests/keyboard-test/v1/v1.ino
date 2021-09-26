#include <Arduino.h>
#include <Wire.h>

#include <HID.h>
#include <Adafruit_BluefruitLE_SPI.h>


#define LEFT_I2C  0b00100100
#define RIGHT_I2C 0b00100000



void setup_i2c() {
    Wire.begin();

    Wire.beginTransmission(LEFT_I2C);
    Wire.write(0x06);
    Wire.write(0b11000000);
    Wire.endTransmission();

    Wire.beginTransmission(LEFT_I2C);
    Wire.write(0x07);
    Wire.write(0b00001111); // 0 = output, 1 = input
    Wire.endTransmission();

    Wire.beginTransmission(RIGHT_I2C);
    Wire.write(0x06);
    Wire.write(0b11000000);
    Wire.endTransmission();

    Wire.beginTransmission(RIGHT_I2C);
    Wire.write(0x07);
    Wire.write(0b00001111);
    Wire.endTransmission();
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

void setup_hid(){
    static HIDSubDescriptor node(_hidReportDescriptor, sizeof(_hidReportDescriptor));
    HID().AppendDescriptor(&node);
}


Adafruit_BluefruitLE_SPI ble(8, 7, 4);

void setup_ble() {
    ble.begin();
    ble.echo(false); 

    bool no_error = true;

    // set name and hid class, enable bleKeyboard
    no_error |= ble.sendCommandCheckOK(F( "AT+GAPDEVNAME=Splitboard Anto"));

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


void setup() {
    Serial.begin(9600);
    delay(50);
    setup_i2c();
    setup_hid();
    setup_ble();
}

byte getLine(int adress, uint8_t line) // return the byte 00abcdef
{
    // set the line to high
    Wire.beginTransmission(adress);
    Wire.write(0x03);
    uint8_t pin = 4 + line;
    Wire.write(~ (1<<pin));
    Wire.endTransmission();

    // request state of 2 buffers
    Wire.beginTransmission(adress);
    Wire.write(0x00);
    Wire.endTransmission();

    Wire.requestFrom(adress, 1);
    byte buff0 = Wire.read();
    Wire.endTransmission();

    Wire.beginTransmission(adress);
    Wire.write(0x01);
    Wire.endTransmission();

    Wire.requestFrom(adress, 1);
    byte buff1 = Wire.read();
    Wire.endTransmission();


    // put together the 2 outputs:
    // return value = byte between 0b000000 and 0b111111

    // we want = abdcef (state of keyboard on that line)
    // buff0 = efxxxxxx
    // buff1 = xxxxabcd
    return ~((buff0 & 0b11000000) >> 6 | (buff1 & 0b00001111) << 2);
}

bool matrix[12*4];

void readKeys() {
    for (int y=0; y<4; y++)
    {
        byte left = getLine(LEFT_I2C, y);
        byte right = getLine(RIGHT_I2C, y);

        for (int x=0; x<6; x++)
        {
            bool pressed = (left >> (5-x)) & 1;
            matrix[y*12+x] = pressed;
        }

        for (int x=0; x<6; x++)
        {
            bool pressed = (right >> (5-x)) & 1;
            matrix[y*12+6+x] = pressed;
        }
    }
}


#define KEY_NONE 0x00 // No key pressed
#define KEY_A 0x04 // Keyboard a and A
#define KEY_B 0x05 // Keyboard b and B
#define KEY_C 0x06 // Keyboard c and C
#define KEY_D 0x07 // Keyboard d and D
#define KEY_E 0x08 // Keyboard e and E
#define KEY_F 0x09 // Keyboard f and F
#define KEY_G 0x0a // Keyboard g and G
#define KEY_H 0x0b // Keyboard h and H
#define KEY_I 0x0c // Keyboard i and I
#define KEY_J 0x0d // Keyboard j and J
#define KEY_K 0x0e // Keyboard k and K
#define KEY_L 0x0f // Keyboard l and L
#define KEY_M 0x10 // Keyboard m and M
#define KEY_N 0x11 // Keyboard n and N
#define KEY_O 0x12 // Keyboard o and O
#define KEY_P 0x13 // Keyboard p and P
#define KEY_Q 0x14 // Keyboard q and Q
#define KEY_R 0x15 // Keyboard r and R
#define KEY_S 0x16 // Keyboard s and S
#define KEY_T 0x17 // Keyboard t and T
#define KEY_U 0x18 // Keyboard u and U
#define KEY_V 0x19 // Keyboard v and V
#define KEY_W 0x1a // Keyboard w and W
#define KEY_X 0x1b // Keyboard x and X
#define KEY_Y 0x1c // Keyboard y and Y
#define KEY_Z 0x1d // Keyboard z and Z

#define KEY_1 0x1e // Keyboard 1 and !
#define KEY_2 0x1f // Keyboard 2 and @
#define KEY_3 0x20 // Keyboard 3 and #
#define KEY_4 0x21 // Keyboard 4 and $
#define KEY_5 0x22 // Keyboard 5 and %
#define KEY_6 0x23 // Keyboard 6 and ^
#define KEY_7 0x24 // Keyboard 7 and &
#define KEY_8 0x25 // Keyboard 8 and *
#define KEY_9 0x26 // Keyboard 9 and (
#define KEY_0 0x27 // Keyboard 0 and )

#define KEY_ENTER 0x28 // Keyboard Return (ENTER)
#define KEY_ESC 0x29 // Keyboard ESCAPE
#define KEY_BACKSPACE 0x2a // Keyboard DELETE (Backspace)
#define KEY_TAB 0x2b // Keyboard Tab
#define KEY_SPACE 0x2c // Keyboard Spacebar
#define KEY_MINUS 0x2d // Keyboard - and _
#define KEY_EQUAL 0x2e // Keyboard = and +
#define KEY_LEFTBRACE 0x2f // Keyboard [ and {
#define KEY_RIGHTBRACE 0x30 // Keyboard ] and }
#define KEY_BACKSLASH 0x31 // Keyboard \ and |
#define KEY_HASHTILDE 0x32 // Keyboard Non-US # and ~
#define KEY_SEMICOLON 0x33 // Keyboard ; and :
#define KEY_APOSTROPHE 0x34 // Keyboard ' and "
#define KEY_GRAVE 0x35 // Keyboard ` and ~
#define KEY_COMMA 0x36 // Keyboard , and <
#define KEY_DOT 0x37 // Keyboard . and >
#define KEY_SLASH 0x38 // Keyboard / and ?
#define KEY_CAPSLOCK 0x39 // Keyboard Caps Lock

const byte keymap[48] PROGMEM = 
{
    // The standard way HID keyboard work is to emulate a QWERTY, and the OS will translate.
    KEY_TAB, KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T,    KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P, KEY_BACKSPACE,
    KEY_ESC, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G,    KEY_H, KEY_J, KEY_K, KEY_L, KEY_SEMICOLON, KEY_APOSTROPHE,
    KEY_NONE, KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B,   KEY_N, KEY_M, KEY_COMMA, KEY_DOT, KEY_SLASH, KEY_ENTER,
    KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE,    KEY_SPACE,  KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE, KEY_NONE,
};

#define POS(x, y) y*12+x

static const byte modifiers[4] = {
    POS(0, 2),// Left ctrl
    POS(5, 3),// Left shift
    POS(3, 3),// Left Alt
    POS(2, 3),// Left super/windows
    // 4 others but not used
};


bool last_pressed = false;

void sendKeys()
{
    byte keys[8] = {0, 0, 0, 0, 0, 0, 0, 0};

    byte modifier_bits = 0;
    for (int i=0; i<4; i++)
    {
        if (matrix[modifiers[i]]) {
            modifier_bits |= (1<<i);
            matrix[modifiers[i]]=0;
        }
    }

    keys[0] = modifier_bits;
    int n_keys = 0;
    for (int i=0; i<48; i++) 
    {
        if (matrix[i] && (n_keys < 6)) {
            keys[2+n_keys++] = pgm_read_byte(keymap+i);
        }
    }

    // send to USB
    HID().SendReport(2, keys, 8);

    // send to bluetooth
    bool pressed = keys[2];
    //if (pressed && !last_pressed){
    //    //ble.print("AT+BleKeyboardCode=");
    //    ble.print("AT+BleKeyboardCode=");
    //    char code[24];
    //    //sprintf(code, "%04X-%04X-%04X-%04X-%04X-%04X-%04X-%04X", keys[0], keys[1], keys[2], keys[3], keys[4], keys[5], keys[6], keys[7]);
    //    sprintf(code, "%02X-%02X-%02X", keys[0], keys[1], keys[2]);
    //    ble.println(code);
    //    //ble.println('\n');
    //    last_pressed = true;
    //}
    //if (!pressed && last_pressed) {
    //    ble.println("AT+BleKeyboardCode=00-00");
    //}
    //last_pressed = pressed;


    //ble.print("AT+BleKeyboardCode=00-00");
    //Serial.print("AT+BleKeyboardCode=00-00");
}


void loop() {
    readKeys();
    sendKeys();
}

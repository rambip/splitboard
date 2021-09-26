#include <Adafruit_BluefruitLE_SPI.h>
#include <HID.h>

typedef char Modifiers;
typedef char* Keys;

#define L_CTRL      128
#define L_SHIFT     64
#define L_ALT       32
#define L_SUPER     16

#define R_CTRL      8
#define R_SHIFT     4
#define R_ALT       2
#define R_SUPER     1


class _Ble_keyboard
{
    private:
    public:
        _Ble_keyboard();
        bool begin(void);
        void send(Modifiers mod, Keys keys);
};

class _Usb_keyboard
{
    private:
    public:
        _Usb_keyboard();
        void begin(void);
        void send(Modifiers mod, Keys keys);
};


extern _Ble_keyboard Ble_keyboard;
extern _Usb_keyboard Usb_keyboard;

#include <Wire.h>

// represents a 12x4 grid of keys
typedef KeyPress bool*

/*
 * LAYOUT:
 * - left:
 * =====================================
 * |  0  |  1  |  2  |  3  |  4  |  5  |      
 * | 12  | 13  | 14  | 15  | 16  | 17  |      
 * | 24  | 25  | 26  | 27  | 28  | 29  |      
 * \(36) | 37  | 38  | 39  | 40  | 41  /      
 *
 *
 * - right:
 * =====================================
 * |  6  |  7  |  8  |  9  | 10  | 11  |      
 * | 18  | 19  | 20  | 21  | 22  | 23  |      
 * | 30  | 31  | 32  | 33  | 34  | 35  |      
 * \ 42  | 43  | 44  | 45  | 46  |(47) /      
 */


class _Multiplexer
{
    private:
    public:
        void begin(void);
        void setLeft(int pin, bool state);
        void setRight(int pin, bool state);
        bool readLeft(int pin);
        bool readRight(int pin);
        void getKeys(KeyPress destination);
        void setLeds(bool state);
}



extern _Multiplexer Multiplexer;

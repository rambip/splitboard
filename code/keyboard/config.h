// os settings:
#define AZERTY
// #define QWERTY
#include "OS_layouts.h"

/*
 _        _ __   _____  _   _ _____ 
| |      / \\ \ / / _ \| | | |_   _|
| |     / _ \\ V / | | | | | | | |  
| |___ / ___ \| || |_| | |_| | | |  
|_____/_/   \_\_| \___/ \___/  |_|  
*/
                                    
const char _base_layer[36] PROGMEM = 
{
    // TODO: debug "`" and "^" key 
'\t','b','é','p','o','w',      0x80,'v','d','l','j',C_BS,
C_ES,'a','u','i','e',',',      'c','t','s','r','n','m',
C_DEL ,'z','y','x','.','k',     '\'','q','g','h','f','\n',
};

const char _shift_layer[36] PROGMEM = 
{
'\t','B','É','P','O','W',      0x81,'V','D','L','J',C_BS,
C_ES,'A','U','I','E',';',      'C','T','S','R','N','M',
C_DEL ,'Z','Y','X',':','K',     '\"','Q','G','H','F','\n',
};

const char _symb_layer[36] PROGMEM = 
{
    '\t', 0,'@','#','$','%',   '^','&','*','(',')',C_BS,
    C_ES, 0, 0,0,C_LEFT, C_RIGHT,      0  ,'[',']','{','}','\n',
    C_DEL,  0, 0, 0, 0, 0,     0, 0, '<', '>', 0, 0, 
};

const char _num_layer[36] PROGMEM = 
{
    '\t','1','2','3','4','5',   '6','7','8','9','0',C_BS,
    C_BS, 0, 0, 0, 0, 0,        C_HOME,'4','5','6',C_END, '\n',
    C_DEL, 0, 0, 0, 0,           '0',   '1','2','3',0, 0, 
};


// TODO: multimedia, macro layer (with strings)

// modifiers:
// (positions for the thumbs)
// o    |  o  |  o  |  o  |  o  |    |  o  |  o  |  o  |  o  |    o
//  MM  |super| alt | symb|shift|    |space| num | ctrl| fn  |  macro  
// (MM=multimedia)


// layering keys
#define SYMB_LAYER 40
#define SHIFT_LAYER 41
#define NUM_LAYER 43
#define MM_LAYER 37
#define MACRO_LAYER 46

// modifiers keys (are treated after, only for the OS)
#define MODIFIER_ALT 39
#define MODIFIER_SUPER 40
#define MODIFIER_CTRL 44

// space key
#define SPACE 42





// export these variables to keyboard.ino (OS_LAYOUT_MAP)
#ifdef AZERTY

#define OS_LAYOUT_MAP _azerty_map

#endif

#ifdef QWERTY

#define OS_LAYOUT_MAP _qwerty_map

#endif

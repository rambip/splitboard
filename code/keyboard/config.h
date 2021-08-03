// ----------------------
#pragma once           // do not
#include "OS_layouts.h"// touch !
// ----------------------


// os settings:
#define AZERTY
// #define QWERTY



/*
 _        _ __   _____  _   _ _____ 
| |      / \\ \ / / _ \| | | |_   _|
| |     / _ \\ V / | | | | | | | |  
| |___ / ___ \| || |_| | |_| | | |  
|_____/_/   \_\_| \___/ \___/  |_|  

if your're looking for a key and don't know its name,
look inside OS_layouts.h
*/
                                    
const char _base_layer[36] PROGMEM = 
{
    // TODO: debug "`" and "^" key 
'\t','b','é','p','o',0x80,      'w','v','d','l','j',C_BS,
C_ES,'a','u','i','e',',',      'c','t','s','r','n','m',
C_DEL ,'z','y','x','.','\'',     'k','q','g','h','f','\n',
};

const char _shift_layer[36] PROGMEM = 
{
'\t','B','è','P','O',0x81,      'W','V','D','L','J',C_BS,
C_ES,'A','U','I','E',';',      'C','T','S','R','N','M',
C_DEL ,'Z','Y','X',':','\"',     'K','Q','G','H','F','\n',
};

const char _symb_layer[36] PROGMEM = 
{
    '\t', '!' ,'@','#','$','%',        '^','&','*','(',')',C_BS,
C_ES,C_LEFT,C_UP,C_DOWN,C_RIGHT,',',   'ç','[',']','{','}','|',
    C_DEL, '?', C_HOME,C_END,'.', '`',         0, '<', '>', '~', '/', 0, 
};

const char _num_layer[36] PROGMEM = 
{
    '\t','1','2','3','4','5',   '6','7','8','9','0',C_BS,
    C_BS,'=',0,'+','-',',',        0,'4','5','6','0', '\n',
    C_DEL, 0, 0, 0, '.', 0,       '0',   '1','2','3','/',0,  
};


// TODO: multimedia, macro layer (with strings)

/* modifiers:
 (positions for the thumbs)
| o    |  o  |  o  |  o  |  o  |    |  o  |  o  |  o  |  o  |    o   |
|  MM  |super| alt | symb|shift|    |space| num | ctrl| fn  |  macro |

 (MM=multimedia)
*/


// TODO: ctrl+maj ?

// layering keys (to access the corresponding layers)
#define SYMB_LAYER 40
#define SHIFT_LAYER 42
#define NUM_LAYER 43
#define MM_LAYER 37
#define MACRO_LAYER 46

// modifiers keys (are treated after, only for the OS)
#define MODIFIER_ALT 39
#define MODIFIER_SUPER 38
#define MODIFIER_CTRL 44

// space key
#define SPACE 41



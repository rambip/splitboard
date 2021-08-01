#pragma once // file imported multiple times, defined one time ! 
/*
                             _        
 ___ __ __ _ _ _  __ ___  __| |___ ___
(_-</ _/ _` | ' \/ _/ _ \/ _` / -_|_-<
/__/\__\__,_|_||_\__\___/\__,_\___/__/
                                      

KEY_NONE 0x00 // No key pressed
KEY_A 0x04 // Keyboard a and A
KEY_B 0x05 // Keyboard b and B
KEY_C 0x06 // Keyboard c and C
KEY_D 0x07 // Keyboard d and D
KEY_E 0x08 // Keyboard e and E
KEY_F 0x09 // Keyboard f and F
KEY_G 0x0a // Keyboard g and G
KEY_H 0x0b // Keyboard h and H
KEY_I 0x0c // Keyboard i and I
KEY_J 0x0d // Keyboard j and J
KEY_K 0x0e // Keyboard k and K
KEY_L 0x0f // Keyboard l and L
KEY_M 0x10 // Keyboard m and M
KEY_N 0x11 // Keyboard n and N
KEY_O 0x12 // Keyboard o and O
KEY_P 0x13 // Keyboard p and P
KEY_Q 0x14 // Keyboard q and Q
KEY_R 0x15 // Keyboard r and R
KEY_S 0x16 // Keyboard s and S
KEY_T 0x17 // Keyboard t and T
KEY_U 0x18 // Keyboard u and U
KEY_V 0x19 // Keyboard v and V
KEY_W 0x1a // Keyboard w and W
KEY_X 0x1b // Keyboard x and X
KEY_Y 0x1c // Keyboard y and Y
KEY_Z 0x1d // Keyboard z and Z

KEY_1 0x1e // Keyboard 1 and !
KEY_2 0x1f // Keyboard 2 and @
KEY_3 0x20 // Keyboard 3 and #
KEY_4 0x21 // Keyboard 4 and $
KEY_5 0x22 // Keyboard 5 and %
KEY_6 0x23 // Keyboard 6 and ^
KEY_7 0x24 // Keyboard 7 and &
KEY_8 0x25 // Keyboard 8 and *
KEY_9 0x26 // Keyboard 9 and (
KEY_0 0x27 // Keyboard 0 and )

KEY_ENTER 0x28 // Keyboard Return (ENTER)
KEY_ESC 0x29 // Keyboard ESCAPE
KEY_BACKSPACE 0x2a // Keyboard DELETE (Backspace)
KEY_TAB 0x2b // Keyboard Tab
KEY_SPACE 0x2c // Keyboard Spacebar
KEY_MINUS 0x2d // Keyboard - and _
KEY_EQUAL 0x2e // Keyboard = and +
KEY_LEFTBRACE 0x2f // Keyboard [ and {
KEY_RIGHTBRACE 0x30 // Keyboard ] and }
KEY_BACKSLASH 0x31 // Keyboard \ and |
KEY_HASHTILDE 0x32 // Keyboard Non-US # and ~
KEY_SEMICOLON 0x33 // Keyboard ; and :
KEY_APOSTROPHE 0x34 // Keyboard ' and "
KEY_GRAVE 0x35 // Keyboard ` and ~
KEY_COMMA 0x36 // Keyboard , and <
KEY_DOT 0x37 // Keyboard . and >
KEY_SLASH 0x38 // Keyboard / and ?
KEY_CAPSLOCK 0x39 // Keyboard Caps Lock
KEY_DELETE 0x4c

KEY_RIGHT 0x4f
KEY_LEFT 0x50
KEY_DOWN 0x51
KEY_UP 0x52
KEY_HOME 0x47
KEY_END 0x4f
*/

//            _                                   _ _           
// __ _  _ __| |_ ___ _ __    ___ _ _  __ ___  __| (_)_ _  __ _ 
/// _| || (_-<  _/ _ \ '  \  / -_) ' \/ _/ _ \/ _` | | ' \/ _` |
//\__|\_,_/__/\__\___/_|_|_| \___|_||_\__\___/\__,_|_|_||_\__, |
//                                                        |___/ 

// by order of priority:
// - first previous key needed
#define DEAD_GRAVE 0x0100
#define DEAD_CIRCUMFLEX 0x0200
#define DEAD_DIAERESIS 0x0300
#define LOCK 0x0400

// - then modifiers (non exclusive)
#define SHIFT 0x1000
#define ALTGR 0x2000

// - then following key
#define SPACE 0x4000


#define C_BS 0x08// backspace
#define C_ES 0x1b// escape
#define C_DEL 0x10
#define C_HOME 0x90
#define C_END 0x91
#define C_RIGHT 0x92
#define C_LEFT 0x93
#define C_DOWN 0x94
#define C_UP 0x95

// latin1 to azerty

const short _azerty_map[256] PROGMEM = {
    // 0x0...
    0x00,             // NUL
    0x00,             // SOH
    0x00,             // STX
    0x00,             // ETX
    0x00,             // EOT
    0x00,             // ENQ
    0x00,             // ACK  
    0x00,             // BEL
    0x2a,             // BS Backspace
    0x2b,             // TAB Tab
    0x28,             // LF Enter
    0x00,             // VT 
    0x00,             // FF 
    0x00,             // CR 
    0x00,             // SO 
    0x00,             // SI 
    // 0x1 ...
    0x4c,             // DEL
    0x00,             // DC1
    0x00,             // DC2
    0x00,             // DC3
    0x00,             // DC4
    0x00,             // NAK
    0x00,             // SYN
    0x00,             // ETB
    0x00,             // CAN
    0x00,             // EM 
    0x00,             // SUB
    0x29,             // ESC
    0x00,             // FS 
    0x00,             // GS 
    0x00,             // RS 
    0x00,             // US 
    // 0x2...
    0x2c,     //  ' '
    0x38,    // !
    0x20,    // "
    0x20|ALTGR,    // #
    0x30,    // $
    0x34|SHIFT,    // %
    0x1e,    // &
    0x21,          // '
    0x22,    // (
    0x2d,    // )
    0x31,    // *
    0x2e|SHIFT,    // +
    0x10,          // ,
    0x23,    // -
    0x36|SHIFT,          // .
    0x37|SHIFT,          // /
    // 0x3...
    0x27|SHIFT,          // 0
    0x1e|SHIFT,          // 1
    0x1f|SHIFT,          // 2
    0x20|SHIFT,          // 3
    0x21|SHIFT,          // 4
    0x22|SHIFT,          // 5
    0x23|SHIFT,          // 6
    0x24|SHIFT,          // 7
    0x25|SHIFT,          // 8
    0x26|SHIFT,          // 9
    0x37,      // :
    0x36,          // ;
    0x64,      // <
    0x2e,          // =
    0x64|SHIFT,    // >
    0x10|SHIFT,// ?
    //0x4...
    0x27|ALTGR,      // @
   0x14|SHIFT,      // A
    0x05|SHIFT,      // B
    0x06|SHIFT,      // C
    0x07|SHIFT,      // D
    0x08|SHIFT,      // E
    0x09|SHIFT,      // F
    0x0a|SHIFT,      // G
    0x0b|SHIFT,      // H
    0x0c|SHIFT,      // I
    0x0d|SHIFT,      // J
    0x0e|SHIFT,      // K
    0x0f|SHIFT,      // L
    0x33|SHIFT,      // M
    0x11|SHIFT,      // N
    0x12|SHIFT,      // O
    //0x5...
    0x13|SHIFT,      // P
    0x04|SHIFT,      // Q
    0x15|SHIFT,      // R
    0x16|SHIFT,      // S
    0x17|SHIFT,      // T
    0x18|SHIFT,      // U
    0x19|SHIFT,      // V
    0x1d|SHIFT,      // W
    0x1b|SHIFT,      // X
    0x1c|SHIFT,      // Y
    0x1a|SHIFT,      // Z
    0x22|ALTGR,          // [
    0x25|ALTGR,          // bslash
    0x2d|ALTGR,          // ]
    0x26|ALTGR,    // ^
    0x25,    // _
    //0x6...
    0x24|ALTGR|SPACE,// `
    0x14,          // a
    0x05,          // b
    0x06,          // c
    0x07,          // d
    0x08,          // e
    0x09,          // f
    0x0a,          // g
    0x0b,          // h
    0x0c,          // i
    0x0d,          // j
    0x0e,          // k
    0x0f,          // l
    0x33,          // m
    0x11,          // n
    0x12,          // o
    //0x7...
    0x13,          // p
    0x04,          // q
    0x15,          // r
    0x16,          // s
    0x17,          // t
    0x18,          // u
    0x19,          // v
    0x1d,          // w
    0x1b,          // x
    0x1c,          // y
    0x1a,          // z
    0x21|ALTGR,    // {
    0x23|ALTGR,    // |
    0x2e|ALTGR,    // }
    0x1f|ALTGR,    // ~
    0,    // DEL
    //0x8...
    0x24|ALTGR, // ` (dead grave, custom)
    0x2f, // ^ (dead circumflex, custom)
    0x0, // 0x82
    0x0, // 0x83
    0x0, // 0x84
    0x0, // 0x85
    0x0, // 0x86
    0x0, // 0x87
    0x0, // 0x88
    0x0, // 0x89
    0x0, // 0x8a
    0x0, // 0x8b
    0x0, // 0x8c
    0x0, // 0x8d
    0x0, // 0x8e
    0x0, // 0x8f
    //0x9...
    0x47, // Home
    0x4f, // End
    0x4f, // Right
    0x50, // Left
    0x51, // Down
    0x52, // Up
    0x0, // 0x96
    0x0, // 0x97
    0x0, // 0x98
    0x0, // 0x99
    0x0, // 0x9a
    0x0, // 0x9b
    0x0, // 0x9c
    0x0, // 0x9d
    0x0, // 0x9e
    0x0, // 0x9f
    //0xa...
    0x0, // 0xa0
    0x0, // ¡
    0x0, // ¢
    0x30|SHIFT, // £
    0x0, // ¤
    0x0, // ¥
    0x0, // ¦
    0x38|SHIFT, // §
    0x0, // ¨
    0x0, // ©
    0x0, // ª
    0x0, // «
    0x0, // ¬
    0x0, // ­
    0x0, // ®
    0x0, // ¯
    // 0xb...
    0x23|SHIFT, // °
    0x0, // ±
    0x0, // ² :warning: latin9, make a o+e !
    0x0, // ³
    0x0, // ´
    0x31, // µ
    0x0, // ¶
    0x0, // ·
    0x0, // ¸
    0x0, // ¹
    0x0, // º
    0x0, // »
    0x0, // ¼
    0x0, // ½
    0x0, // ¾
    0x0, // ¿
    // 0xc...
    0x14|DEAD_GRAVE, // À
    0x0, // Á
    0x14|DEAD_CIRCUMFLEX, // Â
    0x0, // Ã
    0x14|DEAD_DIAERESIS, // Ä
    0x0, // Å
    0x0, // Æ
    0x26|LOCK, // Ç
    0x08|DEAD_GRAVE|SHIFT, // È
    0x1f|LOCK, // É
    0x08|DEAD_CIRCUMFLEX|SHIFT, // Ê
    0x08|DEAD_DIAERESIS|SHIFT, // Ë
    0x0c|DEAD_GRAVE|SHIFT, // Ì
    0x0, // Í
    0x0c|DEAD_GRAVE|SHIFT, // Î
    0x0c|DEAD_DIAERESIS|SHIFT, // Ï
    // 0xd...
    0x0, // Ð
    0x0, // Ñ
    0x12|DEAD_GRAVE|SHIFT, // Ò
    0x0, // Ó
    0x12|DEAD_GRAVE|SHIFT, // Ô
    0x0, // Õ
    0x12|DEAD_DIAERESIS|SHIFT, // Ö
    0x0, // ×
    0x0, // Ø
    0x18|DEAD_GRAVE|SHIFT, // Ù
    0x0, // Ú
    0x18|DEAD_CIRCUMFLEX|SHIFT, // Û
    0x18|DEAD_DIAERESIS|SHIFT, // Ü
    0x0, // Ý
    0x0, // Þ
    0x0, // ß
    // 0xe...
    0x27, // à
    0x0, // á
    0x14|DEAD_CIRCUMFLEX, // â
    0x0, // ã
    0x14|DEAD_DIAERESIS, // ä
    0x0, // å
    0x0, // æ
    0x26, // ç
    0x24, // è
    0x1f, // é
    0x08|DEAD_CIRCUMFLEX, // ê
    0x08|DEAD_DIAERESIS, // ë
    0x0c|DEAD_GRAVE, // ì
    0x0, // í
    0x0c|DEAD_CIRCUMFLEX, // î
    0x0c|DEAD_DIAERESIS, // ï
    //0xf...
    0x0, // ð
    0x0, // ñ
    0x12|DEAD_GRAVE, // ò
    0x0, // ó
    0x12|DEAD_CIRCUMFLEX, // ô
    0x0, // õ
    0x12|DEAD_DIAERESIS, // ö
    0x0, // ÷
    0x0, // ø
    0x34, // ù
    0x0, // ú
    0x18|DEAD_CIRCUMFLEX, // û
    0x18|DEAD_DIAERESIS, // ü
    0x0, // ý
    0x0, // þ
    0x1c|DEAD_DIAERESIS, // ÿ
};


const short _us_inter_map[256] PROGMEM = {
    0x00,             // NUL
    0x00,             // SOH
    0x00,             // STX
    0x00,             // ETX
    0x00,             // EOT
    0x00,             // ENQ
    0x00,             // ACK  
    0x00,             // BEL
    0x2a,             // BS Backspace
    0x2b,             // TAB Tab
    0x28,             // LF Enter
    0x00,             // VT 
    0x00,             // FF 
    0x00,             // CR 
    0x00,             // SO 
    0x00,             // SI 
    0x00,             // DEL
    0x00,             // DC1
    0x00,             // DC2
    0x00,             // DC3
    0x00,             // DC4
    0x00,             // NAK
    0x00,             // SYN
    0x00,             // ETB
    0x00,             // CAN
    0x00,             // EM 
    0x00,             // SUB
    0x00,             // ESC
    0x00,             // FS 
    0x00,             // GS 
    0x00,             // RS 
    0x00,             // US 
    0x2c,     //  ' '
    0x1e,    // !
    0x34,    // "
    0x20,    // #
    0x21,    // $
    0x22,    // %
    0x24,    // &
    0x34,          // '
    0x26,    // (
    0x27,    // )
    0x31,    // *
    0x2e,    // +
    0x36,          // ,
    0x2d,          // -
    0x37,          // .
    0x38,          // /
    0x27,          // 0
    0x1e,          // 1
    0x1f,          // 2
    0x20,          // 3
    0x21,          // 4
    0x22,          // 5
    0x23,          // 6
    0x24,          // 7
    0x25,          // 8
    0x26,          // 9
    0x33,      // :
    0x33,          // ;
    0x36,      // <
    0x2e,          // =
    0x37,      // >
    0x38,      // ?
    0x1f,      // @
    0x04,      // A
    0x05,      // B
    0x06,      // C
    0x07,      // D
    0x08,      // E
    0x09,      // F
    0x0a,      // G
    0x0b,      // H
    0x0c,      // I
    0x0d,      // J
    0x0e,      // K
    0x0f,      // L
    0x10,      // M
    0x11,      // N
    0x12,      // O
    0x13,      // P
    0x14,      // Q
    0x15,      // R
    0x16,      // S
    0x17,      // T
    0x18,      // U
    0x19,      // V
    0x1a,      // W
    0x1b,      // X
    0x1c,      // Y
    0x1d,      // Z
    0x2f,          // [
    0x31,          // bslash
    0x30,          // ]
    0x23,    // ^
    0x2d,    // _
    0x35,          // `
    0x04,          // a
    0x05,          // b
    0x06,          // c
    0x07,          // d
    0x08,          // e
    0x09,          // f
    0x0a,          // g
    0x0b,          // h
    0x0c,          // i
    0x0d,          // j
    0x0e,          // k
    0x0f,          // l
    0x10,          // m
    0x11,          // n
    0x12,          // o
    0x13,          // p
    0x14,          // q
    0x15,          // r
    0x16,          // s
    0x17,          // t
    0x18,          // u
    0x19,          // v
    0x1a,          // w
    0x1b,          // x
    0x1c,          // y
    0x1d,          // z
    0x2f,    // {
    0x31,    // |
    0x30,    // }
    0x35,    // ~
    0,    // DEL
    0x0, // 0x80
    0x0, // 0x81
    0x0, // 0x82
    0x0, // 0x83
    0x0, // 0x84
    0x0, // 0x85
    0x0, // 0x86
    0x0, // 0x87
    0x0, // 0x88
    0x0, // 0x89
    0x0, // 0x8a
    0x0, // 0x8b
    0x0, // 0x8c
    0x0, // 0x8d
    0x0, // 0x8e
    0x0, // 0x8f
    0x0, // 0x90
    0x0, // 0x91
    0x0, // 0x92
    0x0, // 0x93
    0x0, // 0x94
    0x0, // 0x95
    0x0, // 0x96
    0x0, // 0x97
    0x0, // 0x98
    0x0, // 0x99
    0x0, // 0x9a
    0x0, // 0x9b
    0x0, // 0x9c
    0x0, // 0x9d
    0x0, // 0x9e
    0x0, // 0x9f
    0x0, // 0xa0
    0x0, // ¡
    0x0, // ¢
    0x0, // £
    0x0, // ¤
    0x0, // ¥
    0x0, // ¦
    0x0, // §
    0x0, // ¨
    0x0, // ©
    0x0, // ª
    0x0, // «
    0x0, // ¬
    0x0, // ­
    0x0, // ®
    0x0, // ¯
    0x0, // °
    0x0, // ±
    0x0, // ²
    0x0, // ³
    0x0, // ´
    0x0, // µ
    0x0, // ¶
    0x0, // ·
    0x0, // ¸
    0x0, // ¹
    0x0, // º
    0x0, // »
    0x0, // ¼
    0x0, // ½
    0x0, // ¾
    0x0, // ¿
    0x0, // À
    0x0, // Á
    0x0, // Â
    0x0, // Ã
    0x0, // Ä
    0x0, // Å
    0x0, // Æ
    0x0, // Ç
    0x0, // È
    0x0, // É
    0x0, // Ê
    0x0, // Ë
    0x0, // Ì
    0x0, // Í
    0x0, // Î
    0x0, // Ï
    0x0, // Ð
    0x0, // Ñ
    0x0, // Ò
    0x0, // Ó
    0x0, // Ô
    0x0, // Õ
    0x0, // Ö
    0x0, // ×
    0x0, // Ø
    0x0, // Ù
    0x0, // Ú
    0x0, // Û
    0x0, // Ü
    0x0, // Ý
    0x0, // Þ
    0x0, // ß
    0x0, // à
    0x0, // á
    0x0, // â
    0x0, // ã
    0x0, // ä
    0x0, // å
    0x0, // æ
    0x0, // ç
    0x0, // è
    0x0, // é
    0x0, // ê
    0x0, // ë
    0x0, // ì
    0x0, // í
    0x0, // î
    0x0, // ï
    0x0, // ð
    0x0, // ñ
    0x0, // ò
    0x0, // ó
    0x0, // ô
    0x0, // õ
    0x0, // ö
    0x0, // ÷
    0x0, // ø
    0x0, // ù
    0x0, // ú
    0x0, // û
    0x0, // ü
    0x0, // ý
    0x0, // þ
    0x0, // ÿ
};

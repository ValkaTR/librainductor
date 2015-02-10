// #############################################################################
//
//
//
// #############################################################################

#ifndef __ushell_h__
#define __ushell_h__

// #############################################################################
// includes of system headers
//

#include <Arduino.h>

// #############################################################################
// includes of local headers
//

#include "CyclicStack.h"
#include "gstring.h"
#include "gslist.h"
#include "garray.h"

G_BEGIN_DECLS

// #############################################################################
// type and constant definitions
//

#define DEBUG 1

#ifdef DEBUG

#define debug_print(name) { Serial.print( "[" ); Serial.print( name ); Serial.println( "]" ); }
#define debug_print1(name, value1) { Serial.print( "[" ); Serial.print( name ); Serial.print( ": " ); Serial.print( value1 ); Serial.println( "]" ); }
#define debug_print2(name, value1, value2) { Serial.print( "[" ); Serial.print( name ); Serial.print( ": " ); Serial.print( value1 ); Serial.print( ", " ); Serial.print( value2 ); Serial.println( "]" ); }
#define debug_print3(name, value1, value2, value3) { Serial.print( "[" ); Serial.print( name ); Serial.print( ": " ); Serial.print( value1 ); Serial.print( ", " ); Serial.print( value2 );  Serial.print( ", " ); Serial.print( value3 ); Serial.println( "]" ); }

#else

#define debug_print(name)
#define debug_print1(name, value1)
#define debug_print2(name, value1, value2)
#define debug_print3(name, value1, value2, value3)

#endif

// #############################################################################
// class declarations
//

/*** Virtual key codes ***/
#define VK_LBUTTON             0x01
#define VK_RBUTTON             0x02
#define VK_CANCEL              0x03
#define VK_MBUTTON             0x04
#define VK_XBUTTON1            0x05
#define VK_XBUTTON2            0x06
/*                             0x07  Undefined */
#define VK_BACK                0x08
#define VK_TAB                 0x09
/*                             0x0A-0x0B  Undefined */
#define VK_CLEAR               0x0C
#define VK_RETURN              0x0D
/*                             0x0E-0x0F  Undefined */
#define VK_SHIFT               0x10
#define VK_CONTROL             0x11
#define VK_MENU                0x12
#define VK_PAUSE               0x13
#define VK_CAPITAL             0x14

#define VK_KANA                0x15
#define VK_HANGEUL             VK_KANA
#define VK_HANGUL              VK_KANA
#define VK_JUNJA               0x17
#define VK_FINAL               0x18
#define VK_HANJA               0x19
#define VK_KANJI               VK_HANJA

/*                             0x1A       Undefined */
#define VK_ESCAPE              0x1B

#define VK_CONVERT             0x1C
#define VK_NONCONVERT          0x1D
#define VK_ACCEPT              0x1E
#define VK_MODECHANGE          0x1F

#define VK_SPACE               0x20
#define VK_PRIOR               0x21		// PAGE UP key
#define VK_NEXT                0x22		// PAGE DOWN key
#define VK_END                 0x23
#define VK_HOME                0x24
#define VK_LEFT                0x25
#define VK_UP                  0x26
#define VK_RIGHT               0x27
#define VK_DOWN                0x28
#define VK_SELECT              0x29
#define VK_PRINT               0x2A /* OEM specific in Windows 3.1 SDK */
#define VK_EXECUTE             0x2B
#define VK_SNAPSHOT            0x2C
#define VK_INSERT              0x2D
#define VK_DELETE              0x2E
#define VK_HELP                0x2F
/* VK_0 - VK-9                 0x30-0x39  Use ASCII instead */
/*                             0x3A-0x40  Undefined */
/* VK_A - VK_Z                 0x41-0x5A  Use ASCII instead */
#define VK_LWIN                0x5B
#define VK_RWIN                0x5C
#define VK_APPS                0x5D
/*                             0x5E Unassigned */
#define VK_SLEEP               0x5F
#define VK_NUMPAD0             0x60
#define VK_NUMPAD1             0x61
#define VK_NUMPAD2             0x62
#define VK_NUMPAD3             0x63
#define VK_NUMPAD4             0x64
#define VK_NUMPAD5             0x65
#define VK_NUMPAD6             0x66
#define VK_NUMPAD7             0x67
#define VK_NUMPAD8             0x68
#define VK_NUMPAD9             0x69
#define VK_MULTIPLY            0x6A
#define VK_ADD                 0x6B
#define VK_SEPARATOR           0x6C
#define VK_SUBTRACT            0x6D
#define VK_DECIMAL             0x6E
#define VK_DIVIDE              0x6F
#define VK_F1                  0x70
#define VK_F2                  0x71
#define VK_F3                  0x72
#define VK_F4                  0x73
#define VK_F5                  0x74
#define VK_F6                  0x75
#define VK_F7                  0x76
#define VK_F8                  0x77
#define VK_F9                  0x78
#define VK_F10                 0x79
#define VK_F11                 0x7A
#define VK_F12                 0x7B
#define VK_F13                 0x7C
#define VK_F14                 0x7D
#define VK_F15                 0x7E
#define VK_F16                 0x7F
#define VK_F17                 0x80
#define VK_F18                 0x81
#define VK_F19                 0x82
#define VK_F20                 0x83
#define VK_F21                 0x84
#define VK_F22                 0x85
#define VK_F23                 0x86
#define VK_F24                 0x87
/*                             0x88-0x8F  Unassigned */
#define VK_NUMLOCK             0x90
#define VK_SCROLL              0x91
#define VK_OEM_NEC_EQUAL       0x92
#define VK_OEM_FJ_JISHO        0x92
#define VK_OEM_FJ_MASSHOU      0x93
#define VK_OEM_FJ_TOUROKU      0x94
#define VK_OEM_FJ_LOYA         0x95
#define VK_OEM_FJ_ROYA         0x96
/*                             0x97-0x9F  Unassigned */
/*
 * differencing between right and left shift/control/alt key.
 * Used only by GetAsyncKeyState() and GetKeyState().
 */
#define VK_LSHIFT              0xA0
#define VK_RSHIFT              0xA1
#define VK_LCONTROL            0xA2
#define VK_RCONTROL            0xA3
#define VK_LMENU               0xA4
#define VK_RMENU               0xA5

#define VK_BROWSER_BACK        0xA6
#define VK_BROWSER_FORWARD     0xA7
#define VK_BROWSER_REFRESH     0xA8
#define VK_BROWSER_STOP        0xA9
#define VK_BROWSER_SEARCH      0xAA
#define VK_BROWSER_FAVORITES   0xAB
#define VK_BROWSER_HOME        0xAC
#define VK_VOLUME_MUTE         0xAD
#define VK_VOLUME_DOWN         0xAE
#define VK_VOLUME_UP           0xAF
#define VK_MEDIA_NEXT_TRACK    0xB0
#define VK_MEDIA_PREV_TRACK    0xB1
#define VK_MEDIA_STOP          0xB2
#define VK_MEDIA_PLAY_PAUSE    0xB3
#define VK_LAUNCH_MAIL         0xB4
#define VK_LAUNCH_MEDIA_SELECT 0xB5
#define VK_LAUNCH_APP1         0xB6
#define VK_LAUNCH_APP2         0xB7

/*                             0xB8-0xB9  Unassigned */
#define VK_OEM_1               0xBA
#define VK_OEM_PLUS            0xBB
#define VK_OEM_COMMA           0xBC
#define VK_OEM_MINUS           0xBD
#define VK_OEM_PERIOD          0xBE
#define VK_OEM_2               0xBF
#define VK_OEM_3               0xC0
/*                             0xC1-0xDA  Unassigned */
#define VK_OEM_4               0xDB
#define VK_OEM_5               0xDC
#define VK_OEM_6               0xDD
#define VK_OEM_7               0xDE
#define VK_OEM_8               0xDF
/*                             0xE0       OEM specific */
#define VK_OEM_AX              0xE1  /* "AX" key on Japanese AX keyboard */
#define VK_OEM_102             0xE2  /* "<>" or "\|" on RT 102-key keyboard */
#define VK_ICO_HELP            0xE3  /* Help key on ICO */
#define VK_ICO_00              0xE4  /* 00 key on ICO */
#define VK_PROCESSKEY          0xE5
#define VK_ICO_CLEAR           0xE6

#define VK_PACKET              0xE7
/*                             0xE8       Unassigned */

#define VK_OEM_RESET           0xE9
#define VK_OEM_JUMP            0xEA
#define VK_OEM_PA1             0xEB
#define VK_OEM_PA2             0xEC
#define VK_OEM_PA3             0xED
#define VK_OEM_WSCTRL          0xEE
#define VK_OEM_CUSEL           0xEF
#define VK_OEM_ATTN            0xF0
#define VK_OEM_FINISH          0xF1
#define VK_OEM_COPY            0xF2
#define VK_OEM_AUTO            0xF3
#define VK_OEM_ENLW            0xF4
#define VK_OEM_BACKTAB         0xF5
#define VK_ATTN                0xF6
#define VK_CRSEL               0xF7
#define VK_EXSEL               0xF8
#define VK_EREOF               0xF9
#define VK_PLAY                0xFA
#define VK_ZOOM                0xFB
#define VK_NONAME              0xFC
#define VK_PA1                 0xFD
#define VK_OEM_CLEAR           0xFE
/*                             0xFF       Unassigned */

struct KEY_EVENT_MODIFIERS
{
	boolean lshift : 1;
	boolean rshift : 1;
	boolean lcontrol : 1;
	boolean lmenu : 1;
	boolean rmenu : 1;
};

// ############################################################################

#define VT100_COLOR_BLACK       0
#define VT100_COLOR_RED         1
#define VT100_COLOR_GREEN       2
#define VT100_COLOR_YELLOW      3
#define VT100_COLOR_BLUE        4
#define VT100_COLOR_MAGENTA     5
#define VT100_COLOR_CYAN        6
#define VT100_COLOR_WHITE       7
#define VT100_COLOR_DEFAULT     9

// ############################################################################

enum XTERM_CONTROL_CHARACTER
{
	/* 7-bit controls */
	XTERM_CC_NONE = 0x00,
	XTERM_CC_INDEX = 'D',
	XTERM_CC_NEXT_LINE = 'E',
	XTERM_CC_TAB_SET = 'H',
	XTERM_CC_REVERSE_INDEX = 'M',
	XTERM_CC_SS2 = 'N',
	XTERM_CC_SS3 = 'O',
	XTERM_CC_DEVICE_CONTROL_STRING = 'P',
	XTERM_CC_START_OF_GUARDED_AREA = 'V',
	XTERM_CC_END_OF_GUARDED_AREA = 'W',
	XTERM_CC_START_OF_STRING = 'X',
	XTERM_CC_RETURN_TERMINAL_ID = 'Z',
	XTERM_CC_CONTROL_SEQUENCE_INTRODUCER = '[',
	XTERM_CC_STRING_TERMINATOR = '\\',
	XTERM_CC_OPERATION_SYSTEM_CONSOLE_COMMAND = ']',
	XTERM_CC_PRIVACY_MESSAGE = '^',
	XTERM_CC_APPLICATION_PROGRAM_CONSOLE_COMMAND = '_',

	/* C1 (8-Bit) Control Characters */
	/*XTERM_CC_NONE = 0x00,
	XTERM_CC_INDEX = 0x84,
	XTERM_CC_NEXT_LINE = 0x85,
	XTERM_CC_TAB_SET = 0x88,
	XTERM_CC_REVERSE_INDEX = 0x8D,
	XTERM_CC_SS2 = 0x8E,
	XTERM_CC_SS3 = 0x8F,
	XTERM_CC_DEVICE_CONTROL_STRING = 0x90,
	XTERM_CC_START_OF_GUARDED_AREA = 0x96,
	XTERM_CC_END_OF_GUARDED_AREA = 0x97,
	XTERM_CC_START_OF_STRING = 0x98,
	XTERM_CC_RETURN_TERMINAL_ID = 0x9A,
	XTERM_CC_CONTROL_SEQUENCE_INTRODUCER = 0x9B,
	XTERM_CC_STRING_TERMINATOR = 0x9C,
	XTERM_CC_OPERATION_SYSTEM_CONSOLE_COMMAND = 0x9D,
	XTERM_CC_PRIVACY_MESSAGE = 0x9E,
	XTERM_CC_APPLICATION_PROGRAM_CONSOLE_COMMAND = 0x9F,*/
};

// #####################################################################

struct USHELL_BUFFER_CELL
{
	char ch;
	unsigned char fg_color;
	unsigned char bg_color;
	bool bold;
	bool underline;
};

struct USHELL_CLASS
{
	// Terminal dimensions
	int x, y;
	int w, h;

	// Double buffering
	struct USHELL_BUFFER_CELL *buffer1;
	struct USHELL_BUFFER_CELL *buffer2;
	struct USHELL_BUFFER_CELL *buffer_current;

	//
	// Key event proccessing variables
	//
	
	char input_escape;
	char input_previous_ch;
	GString *input_escape_buf;        // a string for escape control codes
	GString *input_escape_number;
	enum XTERM_CONTROL_CHARACTER input_control_character;
	struct KEY_EVENT_MODIFIERS input_key_modifiers;

	//
	// Output
	//

	void (*print_callback) ( char *str, void *user_def );
	void *print_user_def;

	//
	// Interface variables
	//
	
	GPtrArray *window_list;
	int active_window;
	struct CYCLIC_STACK *message_bank;
};

// #####################################################################

//
// Messages
//

// sizeof(void *) = 4
// sizeof(enum WINDOW_COMMAND) = 1

enum WINDOW_COMMAND
{
	WM_CREATE = 1,
	WM_DESTROY,
	WM_PAINT,
	WM_KEY_EVENT,
	WM_CHARACTER,
	WM_SERIAL_EVENT
};

struct WINDOW_PAINT_MESSAGE
{
	struct WINDOW_CLASS *window;
	enum WINDOW_COMMAND command;
	struct USHELL_BUFFER_CELL *buffer;
	
	char padding[3];
};

struct WINDOW_KEY_EVENT_MESSAGE
{
	struct WINDOW_CLASS *window;
	enum WINDOW_COMMAND command;
	struct KEY_EVENT_MODIFIERS *key_modifiers;
	char control_character;
	char ch;
	
	char padding[1];
};

struct WINDOW_CHARACTER_MESSAGE
{
	struct WINDOW_CLASS *window;
	enum WINDOW_COMMAND command;
	char ch;
	
	char padding[10];
};

struct WINDOW_SERIAL_EVENT_MESSAGE
{
	struct WINDOW_CLASS *window;
	enum WINDOW_COMMAND command;
	char ch;
	
	char padding[10];
};

struct WINDOW_GENERIC_MESSAGE
{
	struct WINDOW_CLASS *window;
	enum WINDOW_COMMAND command;
	
	char padding[11];
};

//
// Window attributes
//

struct WINDOW_RECT
{
	int x; int y;
	int w; int h;
};

enum WINDOW_BORDER_STYLE
{
	WINDOW_BORDER_NONE = 0,
	WINDOW_BORDER_SINGLE,
	WINDOW_BORDER_DOUBLE
};

struct WINDOW_ATTRIBUTES
{
	char fg_color;
	char bg_color;
	
	enum WINDOW_BORDER_STYLE border_style;
};

//
// Main window class
//

struct WINDOW_CLASS
{
	// Window tree maintanance
	struct WINDOW_CLASS *parent_window;
	GPtrArray *child_window;
	int active_window;

	char *title;
	struct WINDOW_ATTRIBUTES attributes;
	struct WINDOW_RECT rect;

	int cursor_x;
	int cursor_y;	
	struct USHELL_BUFFER_CELL *paint_buffer;

	bool (*create_proc) ( struct WINDOW_CLASS *window, struct WINDOW_GENERIC_MESSAGE *msg, void *user_def );
	bool (*destroy_proc) ( struct WINDOW_CLASS *window, struct WINDOW_GENERIC_MESSAGE *msg, void *user_def );
	bool (*paint_proc) ( struct WINDOW_CLASS *window, struct WINDOW_PAINT_MESSAGE *msg, void *user_def );
	bool (*key_event_proc) ( struct WINDOW_CLASS *window, struct WINDOW_KEY_EVENT_MESSAGE *msg, void *user_def );
	bool (*character_proc) ( struct WINDOW_CLASS *window, struct WINDOW_CHARACTER_MESSAGE *msg, void *user_def );
	bool (*serial_event_proc) ( struct WINDOW_CLASS *window, struct WINDOW_SERIAL_EVENT_MESSAGE *msg, void *user_def );
	
	//int (*wnd_proc) ( struct WINDOW_CLASS *window, enum WINDOW_COMMAND command, int uParam, int vParam );

	// User defined variable to distinguish different windows in a single wnd_proc
	void *user_def;

	// Feedback
	struct USHELL_CLASS *ushell;
};

// #############################################################################
// function declarations
//

// Buffer operations
void ushell_swap_buffers( struct USHELL_CLASS *ushell );
void ushell_copy_rect( struct USHELL_BUFFER_CELL *dst, struct WINDOW_RECT *rect_dst, struct USHELL_BUFFER_CELL *src, struct WINDOW_RECT *rect_src );
void ushell_print_full( struct USHELL_CLASS *ushell, int _x, int _y, bool bold, bool underline, unsigned char fg_color, unsigned char bg_color, char *value );
void ushell_print( struct USHELL_CLASS *ushell, int _x, int _y, char *value );

struct USHELL_CLASS *ushell_init( void (*proccess_print) ( char *, void * ), void *user_def );

void ushell_proccess_loop( struct USHELL_CLASS *ushell, unsigned long tick_value, signed char tick_factor  );
void ushell_proccess_event( struct USHELL_CLASS *ushell, char ch );
void ushell_proccess_print( struct USHELL_CLASS *ushell, char *str );

struct USHELL_WINDOW *ushell_create_window( int x, int y, int w, int h, struct USHELL_WINDOW_ATTRIBUTES *attributes, int (*callback_proc) (struct USHELL_WINDOW *window, int command, int uParam, int vParam ) );

void ushell_register_window( struct USHELL_CLASS *ushell, struct WINDOW_CLASS *window );
void ushell_send_message( struct USHELL_CLASS *ushell, void *msg );
bool ushell_get_message( struct USHELL_CLASS *ushell, void *msg_out );
void ushell_dispatch_message( struct USHELL_CLASS *ushell, void *msg );

void ushell_draw_statusbar( struct USHELL_CLASS *ushell );
bool ushell_paint_proc( struct WINDOW_CLASS *window, struct WINDOW_PAINT_MESSAGE *msg, void *user_def );
bool ushell_serial_event_proc( struct USHELL_CLASS *ushell, struct WINDOW_SERIAL_EVENT_MESSAGE *msg, void *user_def );

void ushell_write_text_full( struct USHELL_CLASS *ushell, int x, int y, bool bold, bool underline, unsigned char fg_color, unsigned char bg_color, char *str, int len );
void ushell_write_text( struct USHELL_CLASS *ushell, int x, int y, char *str );
void ushell_write_cell_full( struct USHELL_CLASS *ushell, int x, int y, bool bold, bool underline, unsigned char fg_color, unsigned char bg_color, char ch );
void ushell_write_cell( struct USHELL_CLASS *ushell, int x, int y, char ch );

//
// Key event proccessing
//

void ushell_proccess_char( struct USHELL_CLASS *ushell, char ch );
void ushell_proccess_escape( struct USHELL_CLASS *ushell, char ch );
void ushell_proccess_key( struct USHELL_CLASS *ushell, char ch, struct KEY_EVENT_MODIFIERS *mod, int code );
void ushell_prompt_reset(struct USHELL_CLASS *ushell );
void ushell_escape_end( struct USHELL_CLASS *ushell );

//void reprint_line( );

struct WINDOW_CLASS *window_create(
	struct USHELL_CLASS *ushell,
	struct WINDOW_CLASS *parent,
	const char *title,
	struct WINDOW_ATTRIBUTES *attributes,
	struct WINDOW_RECT *rect,
	void *user_def
);

void window_write_text_full( struct WINDOW_CLASS *window, int x, int y, bool bold, bool underline, unsigned char fg_color, unsigned char bg_color, char *str, int len );
void window_write_text( struct WINDOW_CLASS *window, int x, int y, char *str );
void window_write_cell_full( struct WINDOW_CLASS *window, int x, int y, bool bold, bool underline, unsigned char fg_color, unsigned char bg_color, char ch );
void window_write_cell( struct WINDOW_CLASS *window, int x, int y, char ch );

// #############################################################################

G_END_DECLS

#endif // __ushell_h__

// #############################################################################


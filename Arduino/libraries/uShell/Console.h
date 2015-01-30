// #############################################################################
//
//
//
// #############################################################################

#ifndef __console_h__
#define __console_h__

// #############################################################################
// includes of system headers
//

#include <Arduino.h>

// #############################################################################
// includes of local headers
//

#include "uShell.h"
#include "gcommon.h"

G_BEGIN_DECLS

// #############################################################################
// type and constant definitions
//

// #############################################################################

enum CONSOLE_SHIFT_DIRECTION
{
	DIRECTION_NONE = 0,
	DIRECTION_UP,
	DIRECTION_LEFT,
	DIRECTION_DOWN,
	DIRECTION_RIGHT,
};

struct CONSOLE_BUFFER_CELL
{
	char ch;
	unsigned char fg_color;
	unsigned char bg_color;
	bool bold;
	bool underline;
};

// #############################################################################
// class declarations
//

struct CONSOLE_CLASS
{
	//
	// Variables
	//

	void (*print_callback) ( char *str, void *user_def );
	void *print_user_def;

	// Terminal dimensions
	int w, h;
	int x, y;

	// Double buffering
	struct CONSOLE_BUFFER_CELL *buffer1;
	struct CONSOLE_BUFFER_CELL *buffer2;
	struct CONSOLE_BUFFER_CELL *buffer_current;
	
	// Feedback
	struct USHELL_CLASS *ushell;
};

// #############################################################################
// function declarations
//

// Global
struct CONSOLE_CLASS *console_init( int _w, int _h );

//
// Methods
//

// Buffer operations

void console_swap_buffers( struct CONSOLE_CLASS *console );
void console_shift_buffer( struct CONSOLE_CLASS *console, enum CONSOLE_SHIFT_DIRECTION dir, unsigned char count );

void console_print_full( struct CONSOLE_CLASS *console, int _x, int _y, bool bold, bool underline, unsigned char fg_color, unsigned char bg_color, char *value );
void console_print( struct CONSOLE_CLASS *console, int _x, int _y, char *value );

void console_copy_rect( struct CONSOLE_CLASS *console, struct CONSOLE_BUFFER_CELL *buffer, int x, int y, int w, int h );

// Private
void p( void (*print_callback) ( char *, void * ), char *fmt, ... );

// #############################################################################

G_END_DECLS

#endif // __console_h__

// #############################################################################


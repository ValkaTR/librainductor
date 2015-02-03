// #############################################################################
//
//
//
// #############################################################################
// includes of system headers
//

#include <Arduino.h>

// #############################################################################
// includes of local headers
//

#include "Console.h"

// #############################################################################
// global variables
//

// #############################################################################
// functions

struct USHELL_CONSOLE *console_init( int _w, int _h )
{
	struct USHELL_CONSOLE *console = (struct USHELL_CONSOLE *) malloc( sizeof(struct USHELL_CONSOLE) );
	memset( console, 0, sizeof(struct USHELL_CONSOLE) );
	
	console->x = 0; console->y = 0;
	console->w = _w; console->h = _h;
	
	// prepare double buffers
	size_t buffer_size = sizeof(struct CONSOLE_BUFFER_CELL) * console->w * console->h;
	console->buffer1 = (struct CONSOLE_BUFFER_CELL *) malloc( buffer_size );
	console->buffer2 = (struct CONSOLE_BUFFER_CELL *) malloc( buffer_size );
	console->buffer_current = console->buffer1;	
	memset( console->buffer1, 0, buffer_size );
	memset( console->buffer2, 0, buffer_size );
	
	return console;
}

// #############################################################################

void console_swap_buffers( struct USHELL_CONSOLE *console )
{

	// Compare buffers and output the difference
	int prev_i = 0;
	int prev_j = 0;
	for( int j = 0; j < console->h; j++ )
	{
		for( int i = 0; i < console->w; i++ )
		{
			// Send data when the cell is different
			int result = memcmp( &console->buffer1[i + j * console->w], &console->buffer2[i + j * console->w], sizeof(struct CONSOLE_BUFFER_CELL) );
			if( result != 0 )
				continue;
			
			// Color change
			String style = "";
			if( console->buffer1[i + j * console->w].bold != console->buffer2[i + j * console->w].bold ||
				console->buffer1[i + j * console->w].fg_color != console->buffer2[i + j * console->w].fg_color ||
				console->buffer1[i + j * console->w].bg_color != console->buffer2[i + j * console->w].bg_color )
			{
				style = "\x1B[";
				style += ( console->buffer_current[i + j * console->w].bold == true ? "1" : "0" );
				style += ";3";
				style += console->buffer_current[i + j * console->w].fg_color;
				style += ";4";
				style += console->buffer_current[i + j * console->w].bg_color;
				style += "m";
			}
				
			// Change coordinates when the flow is extraordinary
			String coordinate = "";
			if( i != prev_i + 1 ||
				j != prev_j )
			{
				coordinate = "\x1B[";
				coordinate += j; coordinate += ";";
				coordinate += i; coordinate += "H";
			}
				
			String output_character( console->buffer_current[i + j * console->w].ch );
			
			//console->print_callback(
			//	(char *) String(coordinate + style + output_character).c_str(),
			//	console->print_user_def
			//);
		}
		//console->print_callback( "\x1B\x5B\x42", console->print_user_def ); // Down
	}
	
	// Swap buffers
	if( console->buffer_current == console->buffer1 )
		console->buffer_current = console->buffer2;
	else
		console->buffer_current = console->buffer1;
}

// #############################################################################

void console_shift_buffer( struct USHELL_CONSOLE *console, enum CONSOLE_SHIFT_DIRECTION dir, unsigned char count )
{
	// Select rows/columns and move "count" times
	// and fill new space with emptiness
	switch( dir )
	{
		case DIRECTION_UP:
		case DIRECTION_DOWN:
		{
			for( int j = count; j < (console->h - count); j++ )	// Horizontal
			for( int i = 0; i < console->w; i++ )	// Vertical
				memcpy( &console->buffer_current[ i + j * console->w ], &console->buffer_current[ i + (j + 1) * console->w ], sizeof(struct CONSOLE_BUFFER_CELL) );
			
			for( int j = console->h - count; j < console->h; j++ )	// Horizontal
			for( int i = 0; i < console->w; i++ )	// Vertical
				memset( &console->buffer_current[ i + j * console->w ], 0, sizeof(struct CONSOLE_BUFFER_CELL) );

			console->y -= 1;

			break;
		}

		case DIRECTION_LEFT:
		case DIRECTION_RIGHT:
		{
			break;
		}
	}
}

// #############################################################################

void console_print( struct USHELL_CONSOLE *console, int _x, int _y, bool bold, bool underline, unsigned char fg_color, unsigned char bg_color, char *value )
{
	// Write characters to current buffer
	// and wordwrap when right edge reached
	size_t len = strlen( value );
	for( int i = 0; i < len; i++ )
	{
		console->buffer_current[ console->x + console->y * console->w ].ch = value[i];
		console->buffer_current[ console->x + console->y * console->w ].fg_color = fg_color;
		console->buffer_current[ console->x + console->y * console->w ].bg_color = bg_color;
		console->buffer_current[ console->x + console->y * console->w ].bold = bold;
		console->buffer_current[ console->x + console->y * console->w ].underline = underline;
		
		console->x++;
		if( console->x >= console->w )
		{
			console->x = 0;
			console->y += 1;
		}
		
		if( console->y >= console->h )
		{
			console_shift_buffer( console, DIRECTION_UP, 1 );
		}
	}
}

void console_print( struct USHELL_CONSOLE *console, int _x, int _y, unsigned char fg_color, char *value )
{
	console_print( console, _x, _y, false, false, fg_color, 9, value );
}

void console_print( struct USHELL_CONSOLE *console, int _x, int _y, char *value )
{
	console_print( console, _x, _y, false, false, 9, 9, value );
}

void console_print( struct USHELL_CONSOLE *console, char *value )
{
	console_print( console, console->x, console->y, false, false, 9, 9, value );
}

// #############################################################################

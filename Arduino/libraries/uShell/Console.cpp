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
#include "gstring.h"
#include "background.xpm"

// #############################################################################
// global variables
//

// $ echo "╔" | iconv -f UTF-8 -t IBM866 | hexdump -C
static const char *ibm866_table_data[256] = {
	"\x00", "\x01", "\x02", "\x03", "\x04", "\x05", "\x06", "\x07", "\x08", "\x09", "\x0A", "\x0B", "\x0C", "\x0D", "\x0E", "\x0F",
	"\x10", "\x11", "\x12", "\x13", "\x14", "\x15", "\x16", "\x17", "\x18", "\x19", "\x1A", "\x1B", "\x1C", "\x1D", "\x1E", "\x1F",
	" ",    "!",    "\"",   "#",    "$",    "%",    "&",    "'",    "(",    ")",    "*",    "+",    ",",    "-",    ".",    "/",
	"0",    "1",    "2",    "3",    "4",    "5",    "6",    "7",    "8",    "9",    ":",    ";",    "<",    "=",    ">",    "?",
	"@",    "A",    "B",    "C",    "D",    "E",    "F",    "G",    "H",    "I",    "J",    "K",    "L",    "M",    "N",    "O",
	"P",    "Q",    "R",    "S",    "T",    "U",    "V",    "W",    "X",    "Y",    "Z",    "[",    "\\",   "]",    "^",    "_",
	"`",    "a",    "b",    "c",    "d",    "e",    "f",    "g",    "h",    "i",    "j",    "k",    "l",    "m",    "n",    "o",
	"p",    "q",    "r",    "s",    "t",    "u",    "v",    "w",    "x",    "y",    "z",    "{",    "|",    "}",    "~",    "\x7F",
	"А",    "Б",    "В",    "Г",    "Д",    "Е",    "Ж",    "З",    "И",    "Й",    "К",    "Л",    "М",    "Н",    "О",    "П",
	"Р",    "С",    "Т",    "У",    "Ф",    "Х",    "Ц",    "Ч",    "Ш",    "Щ",    "Ъ",    "Ы",    "Ь",    "Э",    "Ю",    "Я",
	"а",    "б",    "в",    "г",    "д",    "е",    "ж",    "з",    "и",    "й",    "к",    "л",    "м",    "н",    "о",    "п",
	"░",    "▒",    "▓",    "│",    "┤",    "╡",    "╢",    "╖",    "╕",    "╣",    "║",    "╗",    "╝",    "╜",    "╛",    "┐",
	"└",    "┴",    "┬",    "├",    "─",    "┼",    "╞",    "╟",    "╚",    "╔",    "╩",    "╦",    "╠",    "═",    "╬",    "╧",
	"╨",    "╤",    "╥",    "╙",    "╘",    "╒",    "╓",    "╫",    "╪",    "┘",    "┌",    "█",    "▄",    "▌",    "▐",    "▀",
	"р",    "с",    "т",    "у",    "ф",    "х",    "ц",    "ч",    "ш",    "щ",    "ъ",    "ы",    "ь",    "э",    "ю",    "я",
	"Ё",    "ё",    "Є",    "є",    "Ї",    "ї",    "Ў",    "ў",    "°",    "∙",    "·",    "√",    "№",    "¤",    "■",    "\xFF"
};

// #############################################################################
// functions

// #############################################################################

double pdf_normal( double x, double m, double s )
{
	//           y
	//
	//           ^       Density function
	//           *
	//          *|*
	//         * | *
	//         * | *
	//        *  |  *
	// -******---+---******-> x
	//
	return exp( - pow(x - m, 2) / ( 2 * pow(s, 2) ) ) / (sqrt(2) * sqrt(3.14159) * s);
}

double cdf_normal( double x, double m, double s )
{
	//           y
	//
	//           ^       Distribute function
	//  1.0 ---  |   *****
	//           | **
	//           |*  
	//          *|  
	//        ** |   
	// -******---+----------> x
	//
	return erf( (x - m) / (s * sqrt(2)) ) / 2 + 1/2;
}

// #############################################################################

struct CONSOLE_CLASS *console_init( int _w, int _h )
{
	struct CONSOLE_CLASS *console = (struct CONSOLE_CLASS *) malloc( sizeof(struct CONSOLE_CLASS ) );
	memset( console, 0, sizeof(struct CONSOLE_CLASS ) );
	
	console->x = 0; console->y = 0;
	console->w = _w; console->h = _h;
	
	// Prepare double buffers
	size_t buffer_size = sizeof(struct CONSOLE_BUFFER_CELL) * console->w * console->h;
	console->buffer1 = (struct CONSOLE_BUFFER_CELL *) malloc( buffer_size );
	console->buffer2 = (struct CONSOLE_BUFFER_CELL *) malloc( buffer_size );
	console->buffer_current = console->buffer1;	
	memset( console->buffer1, 0, buffer_size );
	memset( console->buffer2, 0, buffer_size );
	
	if( console->buffer1 == NULL ) Serial.println( "assert failed: console->buffer1 == NULL" );
	if( console->buffer2 == NULL ) Serial.println( "assert failed: console->buffer2 == NULL" );
	
	// Background
	for( int j = 0; j < console->h; j++ )
	{
		for( int i = 0; i < console->w; i++ )
		{
			switch( background_xpm[j + 5][i] )
			{
				case '@': console->buffer_current[i + j * console->w].ch = 0xFA /* · */; break;
				case '+': console->buffer_current[i + j * console->w].ch = 0xB0 /* ░ */; break;
				case '.': console->buffer_current[i + j * console->w].ch = 0xB1 /* ▒ */; break;
				case ' ': console->buffer_current[i + j * console->w].ch = 0xB2 /* ▓ */; break;
			}
			console->buffer_current[i + j * console->w].fg_color = VT100_COLOR_WHITE;
			console->buffer_current[i + j * console->w].bg_color = VT100_COLOR_BLUE;
		}
	}
	
	return console;
}

// #############################################################################

void console_swap_buffers( struct CONSOLE_CLASS *console )
{
	GString *style = g_string_sized_new( 32 );
	GString *coordinate = g_string_sized_new( 32 );
	GString *output = g_string_sized_new( 32 );

	// Compare buffers and output the difference
	int prev_i = 0;
	int prev_j = 0;
	for( int j = 0; j < console->h; j++ )
	{
		for( int i = 0; i < console->w; i++ )
		{
			if( console->buffer1[i + j * console->w].ch == console->buffer2[i + j * console->w].ch )
			{
				prev_i = i;
				continue;
			}
			
			// Color change
			g_string_truncate( style, 0 );
			if( console->buffer1[i + j * console->w].bold != console->buffer2[i + j * console->w].bold ||
				console->buffer1[i + j * console->w].fg_color != console->buffer2[i + j * console->w].fg_color ||
				console->buffer1[i + j * console->w].bg_color != console->buffer2[i + j * console->w].bg_color )
			{
				char num_tmp[32];
				
				g_string_append( style, "\x1B[" );
				g_string_append( style, ( console->buffer_current[i + j * console->w].bold == true ? "1" : "0" ) );
				g_string_append( style, ";3" );
				itoa( console->buffer_current[i + j * console->w].fg_color, num_tmp, 10 );
				g_string_append( style, num_tmp );
				g_string_append( style, ";4" );
				itoa( console->buffer_current[i + j * console->w].bg_color, num_tmp, 10 );
				g_string_append( style, num_tmp );
				g_string_append( style, "m" );
			}

			// Change coordinates when the flow is extraordinary
			g_string_truncate( coordinate, 0 );
			
			// TODO: Optimize coordinate change (reduce bandwidth usage)
			//if( i != prev_i + 1 || j != prev_j )
			{
				prev_j = j;
				
				char num_tmp[32];
				
				g_string_append( coordinate, "\x1B[" );
				itoa( j + 1, num_tmp, 10 );
				g_string_append( coordinate, num_tmp );
				
				g_string_append_c( coordinate, ';' );
				itoa( i + 1, num_tmp, 10 );
				g_string_append( coordinate, num_tmp );
				g_string_append_c( coordinate, 'H' );
			}
			
			g_string_truncate( output, 0 );
			g_string_append( output, coordinate->str );
			g_string_append( output, style->str );
			
			char ch = console->buffer_current[i + j * console->w].ch;
			if( ch != 0 )
			{
				//g_string_append_c( output, ch );
				g_string_append( output, ibm866_table_data[ch] );
				console->print_callback( output->str, console->print_user_def );
			}
			else
			{
				console->print_callback( " ", console->print_user_def ); // Right
				//console->print_callback( "\x1B\x5B\x43", console->print_user_def ); // Right
			}
			
			prev_i = i;
		}
	}

	// Restore cursor position and show
	{
		struct WINDOW_CLASS *win = window_get_active( console->ushell );
		if( win != NULL )
		{
			char num_tmp[32];
			
			g_string_append( coordinate, "\x1B[" );
			itoa( win->rect.y + win->cursor_y + 1, num_tmp, 10 );
			g_string_append( coordinate, num_tmp );
			
			g_string_append_c( coordinate, ';' );
			itoa( win->rect.x + win->cursor_x + 1, num_tmp, 10 );
			g_string_append( coordinate, num_tmp );
			g_string_append_c( coordinate, 'H' );
			
			console->print_callback( coordinate->str, console->print_user_def );
		}
	}

	g_string_free( output, true );
	g_string_free( coordinate, true );
	g_string_free( style, true );
	
	// Swap buffers
	size_t buffer_size = sizeof(struct CONSOLE_BUFFER_CELL) * console->w * console->h;
	if( console->buffer_current == console->buffer1 )
	{
		console->buffer_current = console->buffer2;
		memcpy( console->buffer_current, console->buffer1, buffer_size );
	}
	else
	{
		console->buffer_current = console->buffer1;
		memcpy( console->buffer_current, console->buffer2, buffer_size );
	}
}

// #############################################################################

void console_print_full( struct CONSOLE_CLASS *console, int _x, int _y, bool bold, bool underline, unsigned char fg_color, unsigned char bg_color, char *value )
{
	// Write characters to current buffer
	// and wordwrap when right edge reached
	size_t len = strlen( value );
	int j = 0;
	for( int i = 0; i < len; i++ )
	{
		console->buffer_current[ _x + i + (_y + j) * console->w ].ch = value[i];
		console->buffer_current[ _x + i + (_y + j) * console->w ].fg_color = fg_color;
		console->buffer_current[ _x + i + (_y + j) * console->w ].bg_color = bg_color;
		console->buffer_current[ _x + i + (_y + j) * console->w ].bold = bold;
		console->buffer_current[ _x + i + (_y + j) * console->w ].underline = underline;
		
		if( i >= console->w )
		{
			i = 0;
			j += 1;
		}
		
		if( j >= console->h )
		{
			return;
		}
	}
}


void console_print( struct CONSOLE_CLASS *console, int _x, int _y, char *value )
{
	console_print_full( console, _x, _y, false, false, 9, 9, value );
}

// #############################################################################

void console_copy_rect( struct CONSOLE_CLASS *console, struct CONSOLE_BUFFER_CELL *buffer, int x, int y, int w, int h )
{
	for( int j = 0; j < h; j++ )
	for( int i = 0; i < w; i++ )
	{
		memcpy(
			&console->buffer_current[(i + x) + (j + y) * console->w],
			&buffer[i + j * w],
			sizeof(struct CONSOLE_BUFFER_CELL)
		);
	}
}

// #############################################################################

// #############################################################################

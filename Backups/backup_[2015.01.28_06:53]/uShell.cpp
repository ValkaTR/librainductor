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

#include "uShell.h"

// #############################################################################
// global variables
//

// #############################################################################
// functions

struct USHELL_CLASS *ushell_init(
	char *prompt,
	struct CONSOLE_COMMAND *cmd_list,
	void (*proccess_print) ( char *, void * ),
	void *user_def
)
{
	struct USHELL_CLASS *ushell = (struct USHELL_CLASS *) malloc( sizeof(struct USHELL_CLASS) );
	memset( ushell, 0, sizeof(struct USHELL_CLASS) );
	ushell->cmd_escape_buf = g_string_sized_new( 32 );
	ushell->cmd_number = g_string_sized_new( 32 );
	ushell->cmd_escape = false;
	ushell->cmd_prev_ch = 0;
	ushell->print_callback = proccess_print;
	ushell->print_user_def = user_def;

	struct CONSOLE_CLASS  *console = (struct CONSOLE_CLASS  *) console_init( 80, 24 );
	console->print_callback = proccess_print;
	console->print_user_def = user_def;
	ushell->console = console;

	console_print( console, 1, 4, "Welcome to Arduino Due!" );
	console_print( console, 1, 5, "Type 'help' for available commands." );
	console_print( console, 1, 6, prompt );
	console_swap_buffers( console );
	
	//ushell->print_callback( "LOVE IS THE SOLUTION TO EVERYTHING!!!1\r\n", ushell->print_user_def );

	return ushell;
}

// ############################################################################

void ushell_proccess_loop( struct USHELL_CLASS *ushell )
{
	// TODO: Timers and redraw
}

// ############################################################################

void ushell_proccess_event( struct USHELL_CLASS *ushell, char ch )
{
	// Debug
	//ushell->print_callback( (char *) String( (unsigned int) ch ).c_str( ), ushell->print_user_def );
	//Serial.print( (unsigned char) ch );
	//Serial.print( " " );

	if( ushell->cmd_escape_buf->len > 0 )
		ushell_proccess_escape( ushell, ch );
	else
		ushell_proccess_char( ushell, ch );

	ushell->cmd_prev_ch = ch;
}

// ############################################################################

void ushell_escape_end( struct USHELL_CLASS *ushell )
{
	g_string_truncate( ushell->cmd_number, 0 );
	g_string_truncate( ushell->cmd_escape_buf, 0 );
}

// ############################################################################
/* 27 91 51 126 del
27 91 49 126 home
27 91 52 126 end
27 91 50 126 ins
27 91 53 126 pgup
27 91 54 126 pgdn */

void ushell_proccess_escape( struct USHELL_CLASS *ushell, char ch )
{
	//p( " %2X ", ch );

	// Store control code string in buffer
	g_string_append_c( ushell->cmd_escape_buf, ch );

	// Detect first character after escape
	// First character is the control code
	if( ushell->cmd_escape_buf->len == 2 )
	{
		ushell->cmd_control_character = (enum XTERM_CONTROL_CHARACTER) ch;
		return;
	}

	// Reset, if parse failed
	if( ushell->cmd_escape_buf->len > 9 )
	{
		ushell_escape_end( ushell );
		return;
	}

	switch( ushell->cmd_control_character )
	{
		case XTERM_CC_CONTROL_SEQUENCE_INTRODUCER:
		{
			switch( ch )
			{
				case 'A':		// Cursor Up 1B 5B 41
				case 'B':		// Cursor Down 1B 5B 42
				case 'C':		// Cursor Right 1B 5B 43
				case 'D':		// Cursor Left 1B 5B 44
				{
					ushell_escape_end( ushell );

					// Convert function key to key code
					int code = 0;
					switch( ch )
					{
						case 'A': code = VK_UP; break;
						case 'B': code = VK_DOWN; break;
						case 'C': code = VK_RIGHT; break;
						case 'D': code = VK_LEFT; break;
					}

					ushell_proccess_key( ushell, 0, ushell->mods, code );

					break;
				}

				case '0' ... '9':
				{
					g_string_append_c( ushell->cmd_number, ch );
					break;
				}

				case ';':
				{
					break;
				}

				case '~':
				{
					// PC-Style Function Keys
					// VT220, 6-key editing keypad

					int n = atoi( ushell->cmd_number->str );
					ushell_escape_end( ushell );

					int code = 0;
					switch( n )
					{
						case 1: code = VK_HOME; break;		// 1B 5B 31 7E ^[[1~
						case 2: code = VK_INSERT; break;	// 1B 5B 32 7E ^[[2~
						case 3: code = VK_DELETE; break;
						case 4: code = VK_END; break;
						case 5: code = VK_PRIOR; break;		// PAGE UP key
						case 6: code = VK_NEXT; break;		// PAGE DOWN key
						case 15: code = VK_F5; break;
						case 17: code = VK_F6; break;
						case 18: code = VK_F7; break;
						case 19: code = VK_F8; break;
						case 20: code = VK_F9; break;
						case 21: code = VK_F10; break;
						case 23: code = VK_F11; break;
						case 24: code = VK_F12; break;
					}

					ushell_proccess_key( ushell, 0, ushell->mods, code );

					break;
				}

				default:
				{
					break;
				}
			}

			break;
		}

		case XTERM_CC_SS3:
		{
			switch( ch )
			{
				case 'P':		// F1 1B 4F 50 ^[OP
				case 'Q':		// F2 1B 4F 51 ^[OQ
				case 'R':		// F3 1B 4F 52 ^[OR
				case 'S':		// F4 1B 4F 53 ^[OS
				{
					ushell_escape_end( ushell );

					// Convert function key to key code
					int code = 0;
					switch( ch )
					{
						case 'P': code = VK_F1; break;
						case 'Q': code = VK_F2; break;
						case 'R': code = VK_F3; break;
						case 'S': code = VK_F4; break;
					}

					ushell_proccess_key( ushell, 0, ushell->mods, code );

					break;
				}
			}

			break;
		}

		// Unknown control code
		default:
		{
			ushell_escape_end( ushell );
		}
	}
}

// ############################################################################

void ushell_proccess_char( struct USHELL_CLASS *ushell, char ch )
{
	switch( ch )
	{
		case 0x01B:		// Escape
		{
			g_string_append_c( ushell->cmd_escape_buf, ch );
			break;
		}

		default:
		{
			// TODO: Send character to active window

			break;
		}
	}
}

// ############################################################################

/**
 *
 * name: proccess_key
 * @param ch character associated with the key
 * @param mod modifier key(s), such as "Shift", or "Ctrl+Shift"
 * @param code value indicating a physical key, such as "HOME", "F1" or "A"
 * @return
 *
 */
void ushell_proccess_key( struct USHELL_CLASS *ushell, char ch, struct KEY_EVENT_MODIFIERS mod, int code )
{
	// TODO: Send key event to active window
	
	return;
	
	// Debug
	switch( code )
	{
		case VK_UP: { ushell->print_callback( "[ Up ]", ushell->print_user_def ); break; }
		case VK_DOWN: { ushell->print_callback( "[ Down ]", ushell->print_user_def ); break; }
		case VK_LEFT: { ushell->print_callback( "[ Left ]", ushell->print_user_def ); break; }
		case VK_RIGHT: { ushell->print_callback( "[ Right ]", ushell->print_user_def ); break; }
		case VK_HOME: { ushell->print_callback( "[ Home ]", ushell->print_user_def ); break; }
		case VK_END: { ushell->print_callback( "[ End ]", ushell->print_user_def ); break; }
		case VK_INSERT: { ushell->print_callback( "[ Insert ]", ushell->print_user_def ); break; }
		case VK_DELETE: { ushell->print_callback( "[ Delete ]", ushell->print_user_def ); break; }
		case VK_NEXT: { ushell->print_callback( "[ PgDn ]", ushell->print_user_def ); break; }
		case VK_PRIOR: { ushell->print_callback( "[ PgUp ]", ushell->print_user_def ); break; }
		case VK_F1: { ushell->print_callback( "[ F1 ]", ushell->print_user_def ); break; }
		case VK_F2: { ushell->print_callback( "[ F2 ]", ushell->print_user_def ); break; }
		case VK_F3: { ushell->print_callback( "[ F3 ]", ushell->print_user_def ); break; }
		case VK_F4: { ushell->print_callback( "[ F4 ]", ushell->print_user_def ); break; }
		case VK_F5: { ushell->print_callback( "[ F5 ]", ushell->print_user_def ); break; }
		case VK_F6: { ushell->print_callback( "[ F6 ]", ushell->print_user_def ); break; }
		case VK_F7: { ushell->print_callback( "[ F7 ]", ushell->print_user_def ); break; }
		case VK_F8: { ushell->print_callback( "[ F8 ]", ushell->print_user_def ); break; }
		case VK_F9: { ushell->print_callback( "[ F9 ]", ushell->print_user_def ); break; }
		case VK_F10: { ushell->print_callback( "[ F10 ]", ushell->print_user_def ); break; }
		case VK_F11: { ushell->print_callback( "[ F11 ]", ushell->print_user_def ); break; }
		case VK_F12: { ushell->print_callback( "[ F12 ]", ushell->print_user_def ); break; }
	}	
}

// #############################################################################

void p( char *fmt, ... )
{
	char tmp[128]; // resulting string limited to 128 chars
	va_list args;
	va_start( args, fmt );
	vsnprintf( tmp, 128, fmt, args );
	va_end( args );
	//print_callback( tmp, NULL );
	Serial.print( tmp );
}

// ############################################################################

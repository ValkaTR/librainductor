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

struct USHELL *ushell_init(
	char *prompt,
	struct CONSOLE_COMMAND *cmd_list,
	void (*proccess_print) ( char *, void * ),
	void *user_def
)
{
	struct USHELL *ushell = (struct USHELL *) malloc( sizeof(struct USHELL) );
	memset( ushell, 0, sizeof(struct USHELL) );
	ushell->cmd_esc_buf.reserve(10);
	ushell->cmd_number.reserve(10);
	ushell->cmd_escape = false;
	ushell->print_callback = (void (*) ( char *, void * )) &proccess_print;
	ushell->print_user_def = user_def;
	
	//struct USHELL_CONSOLE *console = (struct USHELL_CONSOLE *) console_init( 80, 24 );
	//console->print_callback = (void (*) ( char *, void * )) &proccess_print;
	//console->print_user_def = user_def;
	//ushell->console = console;

	//console_print( console, 1, 1, "Welcome to Arduino Due!" );
	//console_print( console, 1, 3, "Type 'help' for available commands." );
	//console_print( console, 0, 5, prompt );
	//console_swap_buffers( console );
	
	p( proccess_print, "LOVE IS THE SOLUTION TO EVERYTHING!!!1\r\n" );

	//ushell->cmd_esc_buf = "111111111111";
	//String test2;
	//test2 = String("\x1B[35m");
	//ushell->cmd_esc_buf += "asdf\r\n";
	//test2 += ushell->cmd_esc_buf;
	char ch = 'Z';
	//ushell->cmd_esc_buf += ch;
	//test2 += ushell->cmd_esc_buf;
	//test2 += String("\x1B[0m \r\n");
	//Serial.print( test2 );

	GString *test = g_string_sized_new( 20 );
	g_string_append( test, "\x1B[35m" );
	g_string_append( test, "1234567890\r\n" );
	g_string_append( test, "ch = " );
	g_string_append_c( test, ch );
	g_string_append( test, "\x1B[0m \r\n" );
	Serial.println( String("test->str =") + test->str ); delay( 250 );

	//char *str = (char *) malloc( 30 );
	//memset( str, 0, 30 );
	//strcat( str, "\x1B[35m" );
	//strcat( str, "asdfghjkl" );
	//strcat( str, "\x1B[0m\r\n" );
	//realloc( str, 50 );
	//strcat( str, "#######################" );
	//Serial.print( str );

	return ushell;
}

// ############################################################################

void ushell_proccess_loop( struct USHELL *ushell )
{
	// TODO: Timers and redraw
}

// ############################################################################

void ushell_proccess_event( struct USHELL *ushell, char ch )
{
	// Debug
	//ushell->print_callback( (char *) String( (unsigned int) ch ).c_str( ), ushell->print_user_def );
	Serial.print( (unsigned int) ch );
	Serial.print( " " );

	//Serial.print( (ushell->cmd_escape == true ? "1true  " : "1false " ) );

	if( ushell->cmd_escape == true )
		ushell_proccess_escape( ushell, ch );
	else
		ushell_proccess_char( ushell, ch );
		
	//Serial.print( (ushell->cmd_escape == true ? "2true  " : "2false " ) );
}

// ############################################################################

void ushell_escape_end( struct USHELL *ushell )
{
	ushell->cmd_number = "";
	ushell->cmd_esc_buf = "";
	ushell->cmd_escape = false;
}

// ############################################################################
/* 27 91 51 126 del
27 91 49 126 home
27 91 52 126 end
27 91 50 126 ins
27 91 53 126 pgup
27 91 54 126 pgdn */

void ushell_proccess_escape( struct USHELL *ushell, char ch )
{
	//p( " %2X ", ch );

	String test1 = "\x1B[31mtesttest\x1B[0m dskjfdsfhj\r\n";
	Serial.print( test1 );

	// Store control code string in buffer
	ushell->cmd_esc_buf += String( ch );
	
	String *test2 = new String( "\x1B[32mtesttest\x1B[0m dskjfdsfhj\r\n" );
	Serial.print( *test2 );

	// Detect first character after escape
	// First character is the control code
	if( ushell->cmd_esc_buf.length( ) == 1 )
	{
		ushell->cmd_control_character = (enum XTERM_CONTROL_CHARACTER) ch;
		return;
	}
	
	String *test3;
	test3 = new String( "\x1B[33mtesttest\x1B[0m dskjfdsfhj\r\n" );
	Serial.print( *test3 );

	// Reset, if parse failed
	if( ushell->cmd_esc_buf.length( ) > 9 )
	{
		ushell_escape_end( ushell );
		return;
	}
	
	String *test4;
	test4 = new String( "\x1B[34mtesttest" );
	*test4 += "\x1B[0m dskjfdsfhj\r\n" ;
	Serial.print( *test4 );

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
					ushell->cmd_number += ch;
					break;
				}

				case ';':
				{
					ushell->cmd_number = "";
					break;
				}

				case '~':
				{
					// PC-Style Function Keys
					// VT220, 6-key editing keypad

					int n = ushell->cmd_number.toInt( );
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

					// add it to the cmd_string:
					//cmd_buffer += ch;
					//cmd_pos += 1;

					//Serial.print( ch );

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
					ushell->cmd_esc_buf = "";
					ushell->cmd_escape = false;

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

void ushell_proccess_char( struct USHELL *ushell, char ch )
{
	//Serial.print( (unsigned int) ch ); Serial.print( " " );
	
	switch( ch )
	{
		case 0x01B:		// Escape
		{
			ushell->cmd_escape = true;

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
void ushell_proccess_key( struct USHELL *ushell, char ch, struct KEY_EVENT_MODIFIERS mod, int code )
{
	// Debug
	switch( code )
	{
		case VK_UP: { p( ushell->print_callback, " Up " ); break; }
		case VK_DOWN: { p( ushell->print_callback, " Down " ); break; }
		case VK_LEFT: { p( ushell->print_callback, " Left " ); break; }
		case VK_RIGHT: { p( ushell->print_callback, " Right " ); break; }
		case VK_HOME: { p( ushell->print_callback, " Home " ); break; }
		case VK_END: { p( ushell->print_callback, " End " ); break; }
		case VK_INSERT: { p( ushell->print_callback, " Insert " ); break; }
		case VK_DELETE: { p( ushell->print_callback, " Delete " ); break; }
		case VK_F1: { p( ushell->print_callback, " F1 " ); break; }
		case VK_F2: { p( ushell->print_callback, " F2 " ); break; }
		case VK_F3: { p( ushell->print_callback, " F3 " ); break; }
		case VK_F4: { p( ushell->print_callback, " F4 " ); break; }
		case VK_F5: { p( ushell->print_callback, " F5 " ); break; }
		case VK_F6: { p( ushell->print_callback, " F6 " ); break; }
		case VK_F7: { p( ushell->print_callback, " F7 " ); break; }
		case VK_F8: { p( ushell->print_callback, " F8 " ); break; }
		case VK_F9: { p( ushell->print_callback, " F9 " ); break; }
		case VK_F10: { p( ushell->print_callback, " F10 " ); break; }
		case VK_F11: { p( ushell->print_callback, " F11 " ); break; }
		case VK_F12: { p( ushell->print_callback, " F12 " ); break; }
	}

	// TODO: Send key event to active window
	
}

// #############################################################################

void p( void (*print_callback) ( char *, void * ), char *fmt, ... )
{
	//char tmp[128]; // resulting string limited to 128 chars
	//va_list args;
	//va_start( args, fmt );
	//vsnprintf( tmp, 128, fmt, args );
	//va_end( args );
	//print_callback( tmp, NULL );
	Serial.print( fmt );
}

// ############################################################################

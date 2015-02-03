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
	ushell->cmd_esc_buf = g_string_sized_new( 32 );
	ushell->cmd_number = g_string_sized_new( 32 );Serial.println( String("cmd_escape_len3: ") + (int) ushell->cmd_escape_len );
	ushell->cmd_escape_len = 22;Serial.println( String("cmd_escape_len4: ") + (int) ushell->cmd_escape_len );
	ushell->cmd_prev_ch = 0;
	//ushell->print_callback = proccess_print;
	//ushell->print_user_def = user_def;
	Serial.println( String("cmd_escape_len5: ") + (int) ushell->cmd_escape_len );
	struct USHELL_CONSOLE *console = (struct USHELL_CONSOLE *) console_init( 80, 24 );
	console->print_callback = proccess_print;
	console->print_user_def = user_def;
	ushell->console = console;
Serial.println( String("cmd_escape_len6: ") + (int) ushell->cmd_escape_len );
	//console_print( console, 1, 1, "Welcome to Arduino Due!" );
	//console_print( console, 1, 3, "Type 'help' for available commands." );
	//console_print( console, 0, 5, prompt );
	//console_swap_buffers( console );
	
	p( proccess_print, "LOVE IS THE SOLUTION TO EVERYTHING!!!1\r\n" );
Serial.println( String("cmd_escape_len7: ") + (int) ushell->cmd_escape_len );
	char ch = 'Z';
	GString *test = g_string_sized_new( 20 );
	g_string_append( test, "\x1B[35m" );
	g_string_append( test, "1234567890\r\n" );
	g_string_append( test, "ch = " );
	g_string_append_c( test, ch );
	g_string_append( test, "\x1B[0m \r\n" );
	Serial.println( String("test->str = ") + test->str ); delay( 250 );
Serial.println( String("cmd_escape_len8: ") + (int) ushell->cmd_escape_len );
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
	//Serial.print( (unsigned char) ch );
	//Serial.print( " " );

	Serial.println( String("cmd_escape_len1: ") + (int) ushell->cmd_escape_len );

	if( ushell->cmd_escape_len > 0 )
		ushell_proccess_escape( ushell, ch );
	else
		ushell_proccess_char( ushell, ch );

	ushell->cmd_prev_ch = ch;
	
	Serial.println( String("cmd_escape_len2: ") + (int) ushell->cmd_escape_len );
}

// ############################################################################

void ushell_escape_end( struct USHELL *ushell )
{
	g_string_truncate( ushell->cmd_number, 0 );
	g_string_truncate( ushell->cmd_esc_buf, 0 );
	ushell->cmd_escape_len = 0;
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
	g_string_append_c( ushell->cmd_esc_buf, ch );
	
	String *test2 = new String( "\x1B[32mtesttest\x1B[0m dskjfdsfhj\r\n" );
	Serial.print( *test2 );

	// Detect first character after escape
	// First character is the control code
	if( ushell->cmd_esc_buf->len == 1 )
	{
		ushell->cmd_control_character = (enum XTERM_CONTROL_CHARACTER) ch;
		return;
	}
	
	String *test3;
	test3 = new String( "\x1B[33mtesttest\x1B[0m dskjfdsfhj\r\n" );
	Serial.print( *test3 );

	// Reset, if parse failed
	if( ushell->cmd_esc_buf->len > 9 )
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
					//g_string_truncate( ushell->cmd_esc_buf, 0 );
					//ushell->cmd_escape_len = false;
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

void ushell_proccess_char( struct USHELL *ushell, char ch )
{
	Serial.print( "process_char\r\n" );
	
	switch( ch )
	{
		case 0x01B:		// Escape
		{Serial.println( String("cmd_escape_len16: ") + (int) ushell->cmd_escape_len );
			Serial.print( "ESCAPE\r\n" );
			ushell->cmd_escape_len = 111;
Serial.println( String("cmd_escape_len17: ") + (int) ushell->cmd_escape_len );
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
		case VK_UP: { Serial.print( " Up " ); break; }
		case VK_DOWN: { Serial.print( " Down " ); break; }
		case VK_LEFT: { Serial.print( " Left " ); break; }
		case VK_RIGHT: { Serial.print( " Right " ); break; }
		case VK_HOME: { Serial.print( " Home " ); break; }
		case VK_END: { Serial.print( " End " ); break; }
		case VK_INSERT: { Serial.print( " Insert " ); break; }
		case VK_DELETE: { Serial.print( " Delete " ); break; }
		case VK_F1: { Serial.print( " F1 " ); break; }
		case VK_F2: { Serial.print( " F2 " ); break; }
		case VK_F3: { Serial.print( " F3 " ); break; }
		case VK_F4: { Serial.print( " F4 " ); break; }
		case VK_F5: { Serial.print( " F5 " ); break; }
		case VK_F6: { Serial.print( " F6 " ); break; }
		case VK_F7: { Serial.print( " F7 " ); break; }
		case VK_F8: { Serial.print( " F8 " ); break; }
		case VK_F9: { Serial.print( " F9 " ); break; }
		case VK_F10: { Serial.print( " F10 " ); break; }
		case VK_F11: { Serial.print( " F11 " ); break; }
		case VK_F12: { Serial.print( " F12 " ); break; }
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

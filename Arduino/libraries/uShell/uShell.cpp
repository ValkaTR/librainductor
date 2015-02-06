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
	
	ushell->message_bank = cyclic_stack_new( sizeof(struct WINDOW_MESSAGE), 8 );
	ushell->window_list = g_ptr_array_sized_new( 8 );

	struct CONSOLE_CLASS  *console = (struct CONSOLE_CLASS  *) console_init( 80, 24 );
	console->ushell = ushell;
	console->print_callback = proccess_print;
	console->print_user_def = user_def;
	ushell->console = console;

	console_print( console, 1, 2, "Welcome to Arduino Due!" );
	console_print( console, 1, 3, "Type 'help' for available commands." );
	console_swap_buffers( console );
	
	//ushell->print_callback( "LOVE IS THE SOLUTION TO EVERYTHING!!!1\r\n", ushell->print_user_def );

	return ushell;
}

// ############################################################################

float timer1 = 0;
void ushell_proccess_loop( struct USHELL_CLASS *ushell, unsigned long tick_value, signed char tick_factor  )
{
	// TODO: Timers and redraw
	float tick = tick_value * pow(10, tick_factor);
	
	/*if( timer1 + 0.2 < tick )
	{
		timer1 = tick;
		GString *str_tmp = g_string_sized_new( 32 );
		
		g_string_printf( str_tmp, "[ %10.1f ]", tick );

		console_print_full( ushell->console, 63, 2, false, false, VT100_COLOR_WHITE, VT100_COLOR_RED, str_tmp->str );
		console_swap_buffers( ushell->console );
		
		g_string_free( str_tmp, true );
	}*/
}

void ushell_add_message( struct USHELL_CLASS *ushell, struct WINDOW_MESSAGE *msg )
{
	cyclic_stack_push( ushell->message_bank, msg );
}

bool ushell_get_message( struct USHELL_CLASS *ushell, struct WINDOW_MESSAGE *msg_out )
{
	// Get latest message
	bool result = cyclic_stack_pop( ushell->message_bank, msg_out );

	return result;
}

void ushell_dispatch_message( struct USHELL_CLASS *ushell, struct WINDOW_MESSAGE *msg )
{
	if( msg != NULL )
	{
		if( msg->window != NULL )
		{
			// Message to the window
			msg->window->wnd_proc( msg->window, msg->command, msg->uParam, msg->vParam );
		}
		else
		{
			// Message to the root
			if( msg->command == WM_SERIAL_EVENT )
			{
				char ch = msg->vParam;
				if( ushell->cmd_escape_buf->len > 0 )
					ushell_proccess_escape( ushell, ch );
				else
					ushell_proccess_char( ushell, ch );

				ushell->cmd_prev_ch = ch;
			}
		}
	}
}

// ############################################################################

void ushell_proccess_event( struct USHELL_CLASS *ushell, char ch )
{
	/*Serial.print( "[proccess_event, " );
	Serial.print( (int) ch );
	Serial.println( "]" );*/
	
	struct WINDOW_MESSAGE msg =
	{
		.window = NULL,
		.command = WM_SERIAL_EVENT,
		.uParam = 0,
		.vParam = ch
	};
	ushell_add_message( ushell, &msg );
}

// ############################################################################

void ushell_escape_end( struct USHELL_CLASS *ushell )
{
	g_string_truncate( ushell->cmd_number, 0 );
	g_string_truncate( ushell->cmd_escape_buf, 0 );
}

// ############################################################################

void ushell_proccess_escape( struct USHELL_CLASS *ushell, char ch )
{
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

					ushell_proccess_key( ushell, 0, &ushell->mods, code );

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

					ushell_proccess_key( ushell, 0, &ushell->mods, code );

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

					ushell_proccess_key( ushell, 0, &ushell->mods, code );

					break;
				}
			}

			break;
		}

		// Unknown control code
		default:
		{
			struct WINDOW_CLASS *win = window_get_active( ushell );
			if( win != NULL )
				window_send_message( win, WM_KEY_EVENT, ushell->cmd_control_character, ch );

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
			// Send character to active window
			struct WINDOW_CLASS *win = window_get_active( ushell );
			if( win != NULL )
				window_send_message( win, WM_CHARACTER, 0, ch );

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
void ushell_proccess_key( struct USHELL_CLASS *ushell, char ch, struct KEY_EVENT_MODIFIERS *mod, int code )
{
	// Send key event to active window
	struct WINDOW_CLASS *win = window_get_active( ushell );
	if( win != NULL )
		window_send_message( win, WM_KEY_EVENT, mod, code );
		
	return;
}

// ############################################################################

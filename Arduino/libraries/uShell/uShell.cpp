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

struct USHELL_CLASS *ushell_init(
	void (*proccess_print) ( char *, void * ),
	void *user_def
)
{
	struct USHELL_CLASS *ushell = (struct USHELL_CLASS *) malloc( sizeof(struct USHELL_CLASS) );
	memset( ushell, 0, sizeof(struct USHELL_CLASS) );
	ushell->input_escape_buf = g_string_sized_new( 32 );
	ushell->input_escape_number = g_string_sized_new( 32 );
	ushell->input_escape = false;
	ushell->input_previous_ch = 0;
	ushell->print_callback = proccess_print;
	ushell->print_user_def = user_def;
	
	ushell->message_bank = cyclic_stack_new( 16, 8 );
	ushell->window_list = g_ptr_array_sized_new( 8 );

	ushell->x = 0; ushell->y = 0;
	ushell->w = 80; ushell->h = 24;
	
	// Prepare double buffers
	size_t buffer_size = sizeof(struct USHELL_BUFFER_CELL) * ushell->w * ushell->h;
	ushell->buffer1 = (struct USHELL_BUFFER_CELL *) malloc( buffer_size );
	ushell->buffer2 = (struct USHELL_BUFFER_CELL *) malloc( buffer_size );
	ushell->buffer_current = ushell->buffer1;	
	memset( ushell->buffer1, 0, buffer_size );
	memset( ushell->buffer2, 0, buffer_size );
	
	// Background
	for( int j = 0; j < ushell->h; j++ )
	{
		for( int i = 0; i < ushell->w; i++ )
		{
			switch( background_xpm[j + 5][i] )
			{
				case '@': ushell->buffer_current[i + j * ushell->w].ch = 0xFA /* · */; break;
				case '+': ushell->buffer_current[i + j * ushell->w].ch = 0xB0 /* ░ */; break;
				case '.': ushell->buffer_current[i + j * ushell->w].ch = 0xB1 /* ▒ */; break;
				case ' ': ushell->buffer_current[i + j * ushell->w].ch = 0xB2 /* ▓ */; break;
			}
			ushell->buffer_current[i + j * ushell->w].fg_color = VT100_COLOR_WHITE;
			ushell->buffer_current[i + j * ushell->w].bg_color = VT100_COLOR_BLUE;
		}
	}

	ushell_print( ushell, 1, 2, "Welcome to Arduino Due!" );
	ushell_print( ushell, 1, 3, "Type 'help' for available commands." );
	ushell_swap_buffers( ushell );
	
	//ushell->print_callback( "LOVE IS THE SOLUTION TO EVERYTHING!!!1\r\n", ushell->print_user_def );

	return ushell;
}

// ############################################################################

float timer1 = 0;
void ushell_proccess_loop( struct USHELL_CLASS *ushell, unsigned long tick_value, signed char tick_factor  )
{
	// TODO: Timers and redraw
	float tick = tick_value * pow(10, tick_factor);
	
	if( timer1 + 0.2 < tick )
	{
		timer1 = tick;
		GString *str_tmp = g_string_sized_new( 32 );
		
		g_string_printf( str_tmp, "[ %10.1f ]", tick );

		ushell_print_full( ushell, 66, ushell->h - 1, false, false, VT100_COLOR_WHITE, VT100_COLOR_RED, str_tmp->str );
		ushell_swap_buffers( ushell );
		
		g_string_free( str_tmp, true );
	}
}

void ushell_send_message( struct USHELL_CLASS *ushell, void *msg )
{
	struct WINDOW_GENERIC_MESSAGE *msg_generic = (struct WINDOW_GENERIC_MESSAGE *) msg;
	
	cyclic_stack_push( ushell->message_bank, msg );
}

bool ushell_get_message( struct USHELL_CLASS *ushell, void *msg_out )
{
	// Get latest message
	bool result = cyclic_stack_pop( ushell->message_bank, msg_out );

	return result;
}

void ushell_dispatch_message( struct USHELL_CLASS *ushell, void *msg )
{
	if( msg == NULL )
		return;
	
	struct WINDOW_GENERIC_MESSAGE *msg_generic = (struct WINDOW_GENERIC_MESSAGE *) msg;
	
	// Select active window if window in the message is not specified
	if( msg_generic->window == NULL )
	if( ushell->window_list->len != 0 )
	{
		msg_generic->window = (struct WINDOW_CLASS *) ushell->window_list->pdata[ushell->active_window];
	}
	
	
	switch( msg_generic->command )
	{
		case WM_CREATE:
		{
			if( msg_generic->window != NULL )
			if( msg_generic->window->create_proc != NULL )
			{
				msg_generic->window->create_proc( msg_generic->window, msg, msg_generic->window->user_def );
			}
			
			break;
		}

		case WM_DESTROY:
		{
			if( msg_generic->window != NULL )
			if( msg_generic->window->destroy_proc != NULL )
			{
				msg_generic->window->destroy_proc( msg_generic->window, msg, msg_generic->window->user_def );
			}
			
			break;
		}
		
		case WM_PAINT:
		{
			ushell_paint_proc( msg_generic->window, msg, ushell );

			if( msg_generic->window != NULL )
			if( msg_generic->window->paint_proc != NULL )
			{
				msg_generic->window->paint_proc( msg_generic->window, msg, msg_generic->window->user_def );
				
				struct WINDOW_RECT rect_dst =
				{
					.x = 0, .y = 0,
					.w = ushell->w,
					.h = ushell->h,
				};
				ushell_copy_rect( ushell->buffer_current, &rect_dst, msg_generic->window->paint_buffer, &msg_generic->window->rect );
			}

			ushell_swap_buffers( ushell );

			break;
		}
		
		case WM_KEY_EVENT:
		{
			//
			// Window switching
			//
			
			struct WINDOW_KEY_EVENT_MESSAGE *msg_key_event = (struct WINDOW_KEY_EVENT_MESSAGE *) msg;
			switch( msg_key_event->ch )
			{
				case 't':	// F5
				{
					//debug_print2( "key_eventN", (int) msg_key_event->window, msg_key_event->ch );
					ushell->active_window += 1;
					if( ushell->active_window == ushell->window_list->len )
						ushell->active_window = 0;
					
					ushell_draw_statusbar( ushell );
					ushell_swap_buffers( ushell );
					return;
				}
				
				case 'u':	// F6
				{
					//debug_print2( "key_eventP", (int) msg_key_event->window, msg_key_event->ch );
					ushell->active_window -= 1;
					if( ushell->active_window == -1 )
						ushell->active_window = ushell->window_list->len - 1;
					
					ushell_draw_statusbar( ushell );
					ushell_swap_buffers( ushell );
					return;
				}
			}

			//debug_print2( "key_event", (int) msg_key_event->window, msg_key_event->ch );

			if( msg_generic->window != NULL )
			if( msg_generic->window->key_event_proc != NULL )
			{
				msg_generic->window->key_event_proc( msg_generic->window, msg, msg_generic->window->user_def );
			}
			
			break;
		}
		
		case WM_CHARACTER:
		{
			if( msg_generic->window != NULL )
			if( msg_generic->window->character_proc != NULL )
			{
				msg_generic->window->character_proc( msg_generic->window, msg, msg_generic->window->user_def );
			}

			break;
		}
		
		case WM_SERIAL_EVENT:
		{
			ushell_serial_event_proc( ushell, msg, NULL );
			
			if( msg_generic->window != NULL )
			if( msg_generic->window->serial_event_proc != NULL )
			{
				msg_generic->window->serial_event_proc( msg_generic->window, msg, msg_generic->window->user_def );
			}
			
			break;
		}
	}
}

// ############################################################################

void ushell_draw_statusbar( struct USHELL_CLASS *ushell )
{
	for( int i = 0; i < ushell->window_list->len; i++ )
	{
		struct WINDOW_CLASS *window = (struct WINDOW_CLASS *) ushell->window_list->pdata[i];

		ushell_write_cell_full( ushell, i * 10, ushell->h - 1, false, false, VT100_COLOR_WHITE, VT100_COLOR_BLUE, '[' );
		ushell_write_cell_full( ushell, (i + 1) * 10 - 1, ushell->h - 1, false, false, VT100_COLOR_WHITE, VT100_COLOR_BLUE, ']' );

		if( ushell->active_window == i )
			ushell_write_text_full( ushell, i * 10 + 1, ushell->h - 1, false, false, VT100_COLOR_WHITE, VT100_COLOR_BLUE, window->title, 8 );
		else
			ushell_write_text_full( ushell, i * 10 + 1, ushell->h - 1, false, false, VT100_COLOR_DEFAULT, VT100_COLOR_DEFAULT, window->title, 8 );
	}
}

// ############################################################################

bool ushell_paint_proc( struct WINDOW_CLASS *window, struct WINDOW_PAINT_MESSAGE *msg, void *user_def )
{
	struct USHELL_CLASS *ushell = (struct USHELL_CLASS *) user_def;
	
	if( window->attributes.border_style == WINDOW_BORDER_DOUBLE )
	{
		// Vertical and Horizontal
		for( int i = 0; i < window->rect.w; i++ ) ushell_write_cell( ushell, window->rect.x + i, window->rect.y - 1, 0xCD /* ═ */ );
		for( int i = 0; i < window->rect.w; i++ ) ushell_write_cell( ushell, window->rect.x + i, window->rect.y + window->rect.h, 0xCD /* ═ */ );
		for( int j = 0; j < window->rect.h; j++ ) ushell_write_cell( ushell, window->rect.x - 1, window->rect.y + j, 0xBA /* ║ */ );
		for( int j = 0; j < window->rect.h; j++ ) ushell_write_cell( ushell, window->rect.x + window->rect.w, window->rect.y + j, 0xBA /* ║ */ );
		
		// Corners
		ushell_write_cell( ushell, window->rect.x - 1, window->rect.y - 1, 0xC9 /* ╔ */ );
		ushell_write_cell( ushell, window->rect.x - 1, window->rect.y + window->rect.h, 0xC8 /* ╚ */ );
		ushell_write_cell( ushell, window->rect.x + window->rect.w, window->rect.y - 1, 0xBB /* ╗ */ );
		ushell_write_cell( ushell, window->rect.x + window->rect.w, window->rect.y + window->rect.h, 0xBC /* ╝ */ );
	}
	else if( window->attributes.border_style == WINDOW_BORDER_SINGLE )
	{
		// Vertical and Horizontal
		for( int i = 0; i < window->rect.w; i++ ) ushell_write_cell( ushell, window->rect.x + i, window->rect.y - 1, 0xC4 /* ─ */ );
		for( int i = 0; i < window->rect.w; i++ ) ushell_write_cell( ushell, window->rect.x + i, window->rect.y + window->rect.h, 0xC4 /* ─ */ );
		for( int j = 0; j < window->rect.h; j++ ) ushell_write_cell( ushell, window->rect.x - 1, window->rect.y + j, 0xB3 /* │ */ );
		for( int j = 0; j < window->rect.h; j++ ) ushell_write_cell( ushell, window->rect.x + window->rect.w, window->rect.y + j, 0xB3 /* │ */ );
		
		// Corners
		ushell_write_cell( ushell, window->rect.x - 1, window->rect.y - 1, 0xDA /* ┌ */ );
		ushell_write_cell( ushell, window->rect.x - 1, window->rect.y + window->rect.h, 0xC0 /* └ */ );
		ushell_write_cell( ushell, window->rect.x + window->rect.w, window->rect.y - 1, 0xBF /* ┐ */ );
		ushell_write_cell( ushell, window->rect.x + window->rect.w, window->rect.y + window->rect.h, 0xD9 /* ┘ */ );
	}

	// Shadow
	//for( int i = 1; i < window->rect.w + 1; i++ ) ushell_write_cell( ushell, i, window->rect.h, 0xB0 /* ░ */ );
	//for( int j = 1; j < window->rect.h + 1; j++ ) ushell_write_cell( ushell, window->rect.w, j, 0xB0 /* ░ */ );
	
	// Title
	if( window->attributes.border_style != WINDOW_BORDER_NONE )
	{
		int title_len = strlen( window->title );
		char title_offset = 4;
		
		ushell_write_text_full( ushell, window->rect.x + title_offset, window->rect.y - 1, false, false, VT100_COLOR_DEFAULT, VT100_COLOR_DEFAULT, window->title, -1 );
		
		ushell_write_cell( ushell, window->rect.x + title_offset - 2, window->rect.y - 1, '[' );
		ushell_write_cell( ushell, window->rect.x + title_offset - 1, window->rect.y - 1, ' ' );
		ushell_write_cell( ushell, window->rect.x + title_offset + title_len, window->rect.y - 1, ' ' );
		ushell_write_cell( ushell, window->rect.x + title_offset + title_len + 1, window->rect.y - 1, ']' );
	}
	
	//if( window_manager->active_window_id == window_id )
	//	ushell_write_text_full( ushell, window_id * 10, ushell->h - 1, false, false, VT100_COLOR_WHITE, VT100_COLOR_BLUE, window->title );
	//else
	//	ushell_write_text_full( ushell, window_id * 10, ushell->h - 1, false, false, VT100_COLOR_DEFAULT, VT100_COLOR_DEFAULT, child_window->title );
	
	return true;
}

// ############################################################################

bool ushell_serial_event_proc( struct USHELL_CLASS *ushell, struct WINDOW_SERIAL_EVENT_MESSAGE *msg, void *user_def )
{

	if( ushell->input_escape_buf->len > 0 )
	{
		//
		// Proccess escape sequence
		//
		
		// Store control code string in buffer
		g_string_append_c( ushell->input_escape_buf, msg->ch );

		// Detect first character after escape
		// First character is the control code
		if( ushell->input_escape_buf->len == 2 )
		{
			ushell->input_control_character = (enum XTERM_CONTROL_CHARACTER) msg->ch;
			return;
		}

		// Reset, if parse failed
		if( ushell->input_escape_buf->len > 9 )
		{
			g_string_truncate( ushell->input_escape_number, 0 );
			g_string_truncate( ushell->input_escape_buf, 0 );
			return;
		}

		switch( ushell->input_control_character )
		{
			case XTERM_CC_CONTROL_SEQUENCE_INTRODUCER:
			{
				switch( msg->ch )
				{
					case 'A':		// Cursor Up 1B 5B 41
					case 'B':		// Cursor Down 1B 5B 42
					case 'C':		// Cursor Right 1B 5B 43
					case 'D':		// Cursor Left 1B 5B 44
					{
						g_string_truncate( ushell->input_escape_number, 0 );
						g_string_truncate( ushell->input_escape_buf, 0 );
			
						// Convert function key to key code
						int code = 0;
						switch( msg->ch )
						{
							case 'A': code = VK_UP; break;
							case 'B': code = VK_DOWN; break;
							case 'C': code = VK_RIGHT; break;
							case 'D': code = VK_LEFT; break;
						}

						struct WINDOW_KEY_EVENT_MESSAGE key_msg =
						{
							.window = msg->window,
							.command = WM_KEY_EVENT,
							.key_modifiers = &ushell->input_key_modifiers,
							.control_character = ushell->input_control_character,
							.ch = code
						};
						
						ushell_send_message( ushell, &key_msg );

						break;
					}

					case '0' ... '9':
					{
						g_string_append_c( ushell->input_escape_number, msg->ch );
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

						int n = atoi( ushell->input_escape_number->str );
						g_string_truncate( ushell->input_escape_number, 0 );
						g_string_truncate( ushell->input_escape_buf, 0 );

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

						struct WINDOW_KEY_EVENT_MESSAGE key_msg =
						{
							.window = msg->window,
							.command = WM_KEY_EVENT,
							.key_modifiers = &ushell->input_key_modifiers,
							.control_character = ushell->input_control_character,
							.ch = code
						};
						
						ushell_send_message( ushell, &key_msg );

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
				switch( msg->ch )
				{
					case 'P':		// F1 1B 4F 50 ^[OP
					case 'Q':		// F2 1B 4F 51 ^[OQ
					case 'R':		// F3 1B 4F 52 ^[OR
					case 'S':		// F4 1B 4F 53 ^[OS
					{
						g_string_truncate( ushell->input_escape_number, 0 );
						g_string_truncate( ushell->input_escape_buf, 0 );

						// Convert function key to key code
						int code = 0;
						switch( msg->ch )
						{
							case 'P': code = VK_F1; break;
							case 'Q': code = VK_F2; break;
							case 'R': code = VK_F3; break;
							case 'S': code = VK_F4; break;
						}

						struct WINDOW_KEY_EVENT_MESSAGE key_msg =
						{
							.window = msg->window,
							.command = WM_KEY_EVENT,
							.key_modifiers = &ushell->input_key_modifiers,
							.control_character = ushell->input_control_character,
							.ch = code
						};
						
						ushell_send_message( ushell, &key_msg );

						break;
					}
				}

				break;
			}

			// Unknown control code
			default:
			{
				struct WINDOW_KEY_EVENT_MESSAGE key_msg =
				{
					.window = msg->window,
					.command = WM_KEY_EVENT,
					.key_modifiers = &ushell->input_key_modifiers,
					.control_character = ushell->input_control_character,
					.ch = msg->ch
				};
				
				ushell_send_message( ushell, &key_msg );

				g_string_truncate( ushell->input_escape_number, 0 );
				g_string_truncate( ushell->input_escape_buf, 0 );
			}
		}
	}
	else
	{
		//
		// Proccess ordinary character
		//

		switch( msg->ch )
		{
			case 0x01B:		// Escape
			{
				g_string_append_c( ushell->input_escape_buf, msg->ch );
				break;
			}

			default:
			{
				// Send character to active window
				struct WINDOW_CHARACTER_MESSAGE char_msg =
				{
					.window = NULL,
					.command = WM_CHARACTER,
					.ch = msg->ch
				};
				
				ushell_send_message( ushell, &char_msg );

				break;
			}
		}
	}

	ushell->input_previous_ch = msg->ch;
}

// ############################################################################

void ushell_proccess_event( struct USHELL_CLASS *ushell, char ch )
{
	struct WINDOW_SERIAL_EVENT_MESSAGE msg =
	{
		.window = NULL,
		.command = WM_SERIAL_EVENT,
		.ch = ch
	};

	ushell_serial_event_proc( ushell, &msg, NULL );

	//ushell_send_message( ushell, &msg );
}

// ############################################################################

void ushell_swap_buffers( struct USHELL_CLASS *ushell )
{
	GString *style = g_string_sized_new( 32 );
	GString *coordinate = g_string_sized_new( 32 );
	GString *output = g_string_sized_new( 32 );

	// Compare buffers and output the difference
	int prev_i = 0;
	int prev_j = 0;
	for( int j = 0; j < ushell->h; j++ )
	{
		for( int i = 0; i < ushell->w; i++ )
		{
			if( ushell->buffer1[i + j * ushell->w].ch == ushell->buffer2[i + j * ushell->w].ch )
			{
				prev_i = i;
				continue;
			}
			
			// Color change
			g_string_truncate( style, 0 );
			//if( ushell->buffer1[i + j * ushell->w].bold != ushell->buffer2[i + j * ushell->w].bold ||
			//	ushell->buffer1[i + j * ushell->w].fg_color != ushell->buffer2[i + j * ushell->w].fg_color ||
			//	ushell->buffer1[i + j * ushell->w].bg_color != ushell->buffer2[i + j * ushell->w].bg_color )
			{
				char num_tmp[32];
				
				g_string_append( style, "\x1B[" );
				g_string_append( style, ( ushell->buffer_current[i + j * ushell->w].bold == true ? "1" : "0" ) );
				g_string_append( style, ";3" );
				itoa( ushell->buffer_current[i + j * ushell->w].fg_color, num_tmp, 10 );
				g_string_append( style, num_tmp );
				g_string_append( style, ";4" );
				itoa( ushell->buffer_current[i + j * ushell->w].bg_color, num_tmp, 10 );
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
			
			char ch = ushell->buffer_current[i + j * ushell->w].ch;
			if( ch != 0 )
			{
				//g_string_append_c( output, ch );
				g_string_append( output, ibm866_table_data[ch] );
				ushell->print_callback( output->str, ushell->print_user_def );
			}
			else
			{
				ushell->print_callback( " ", ushell->print_user_def ); // Right
				//ushell->print_callback( "\x1B\x5B\x43", ushell->print_user_def ); // Right
			}
			
			prev_i = i;
		}
	}

	// Restore cursor position and show
	if( ushell->window_list->len > 0 )
	{
		struct WINDOW_CLASS *win = (struct WINDOW_CLASS *) ushell->window_list->pdata[ushell->active_window];
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
			
			ushell->print_callback( coordinate->str, ushell->print_user_def );
		}
	}

	g_string_free( output, true );
	g_string_free( coordinate, true );
	g_string_free( style, true );

	// Swap buffers
	size_t buffer_size = sizeof(struct USHELL_BUFFER_CELL) * ushell->w * ushell->h;
	if( ushell->buffer_current == ushell->buffer1 )
	{
		ushell->buffer_current = ushell->buffer2;
		memcpy( ushell->buffer_current, ushell->buffer1, buffer_size );
	}
	else
	{
		ushell->buffer_current = ushell->buffer1;
		memcpy( ushell->buffer_current, ushell->buffer2, buffer_size );
	}
}

// #############################################################################

void ushell_print_full( struct USHELL_CLASS *ushell, int _x, int _y, bool bold, bool underline, unsigned char fg_color, unsigned char bg_color, char *value )
{
	// Write characters to current buffer
	// and wordwrap when right edge reached
	size_t len = strlen( value );
	int j = 0;
	for( int i = 0; i < len; i++ )
	{
		ushell->buffer_current[ _x + i + (_y + j) * ushell->w ].ch = value[i];
		ushell->buffer_current[ _x + i + (_y + j) * ushell->w ].fg_color = fg_color;
		ushell->buffer_current[ _x + i + (_y + j) * ushell->w ].bg_color = bg_color;
		ushell->buffer_current[ _x + i + (_y + j) * ushell->w ].bold = bold;
		ushell->buffer_current[ _x + i + (_y + j) * ushell->w ].underline = underline;
		
		if( i >= ushell->w )
		{
			i = 0;
			j += 1;
		}
		
		if( j >= ushell->h )
		{
			return;
		}
	}
}


void ushell_print( struct USHELL_CLASS *ushell, int _x, int _y, char *value )
{
	ushell_print_full( ushell, _x, _y, false, false, 9, 9, value );
}

// #############################################################################

void ushell_copy_rect( struct USHELL_BUFFER_CELL *dst, struct WINDOW_RECT *rect_dst, struct USHELL_BUFFER_CELL *src, struct WINDOW_RECT *rect_src )
{
	for( int j = 0; j < rect_src->h; j++ )
	for( int i = 0; i < rect_src->w; i++ )
	{
		memcpy(
			&dst[(i + rect_src->x) + (j + rect_src->y) * rect_dst->w],
			&src[(i + rect_dst->x) + (j + rect_dst->y) * rect_src->w],
			sizeof(struct USHELL_BUFFER_CELL)
		);
	}
}

// #############################################################################

void ushell_register_window( struct USHELL_CLASS *ushell, struct WINDOW_CLASS *window )
{
	g_ptr_array_add( ushell->window_list, window );

	//
	// Make window appear on the console
	//

	struct WINDOW_GENERIC_MESSAGE generic_msg =
	{
		.window = window,
		.command = WM_CREATE
	};
	
	ushell_send_message( ushell, &generic_msg );
	
	struct WINDOW_PAINT_MESSAGE paint_msg =
	{
		.window = window,
		.command = WM_PAINT,
		.buffer = ushell->buffer_current
	};
	
	ushell_send_message( ushell, &paint_msg );
	
	ushell_draw_statusbar( ushell );
	ushell_swap_buffers( ushell );
}

// #############################################################################
// #############################################################################
// #############################################################################

struct WINDOW_CLASS *window_create(
	struct USHELL_CLASS *ushell,
	struct WINDOW_CLASS *parent,
	const char *title,
	struct WINDOW_ATTRIBUTES *attributes,
	struct WINDOW_RECT *rect,
	void *user_def
)
{
	//
	// Memory allocation and variable copying
	//
	
	struct WINDOW_CLASS *window = (struct WINDOW_CLASS *) malloc( sizeof(struct WINDOW_CLASS) );
	memset( window, 0, sizeof(struct WINDOW_CLASS) );
	
	window->title = (char *) title;

	memcpy( &window->attributes, attributes, sizeof(struct WINDOW_ATTRIBUTES) );
	memcpy( &window->rect, rect, sizeof(struct WINDOW_RECT) );

	size_t buffer_size = window->rect.w * window->rect.h * sizeof(struct USHELL_BUFFER_CELL);
	window->paint_buffer = (struct USHELL_BUFFER_CELL *) malloc( buffer_size );
	memset( window->paint_buffer, 0, buffer_size );
	for( int j = 0; j < window->rect.h; j++ )
	for( int i = 0; i < window->rect.w; i++ )
		window_write_cell( window, i, j, ' ' );

	//window->wnd_proc = wnd_proc;	
	window->user_def = user_def;

	window->ushell = ushell;

	window->child_window = g_ptr_array_new( );
	if( parent != NULL )
	{
		window->parent_window = parent;
		g_ptr_array_add( parent->child_window, window );
	}

	return window;
}

// #############################################################################

void ushell_write_text_full( struct USHELL_CLASS *ushell, int x, int y, bool bold, bool underline, unsigned char fg_color, unsigned char bg_color, char *str, int len )
{
	if( len == -1 )
		len = ushell->w;
	
	for( int i = 0; str[i] != 0; i++ )
	{
		struct USHELL_BUFFER_CELL *cell = &ushell->buffer_current[i + x + y * ushell->w];
		cell->ch = str[i];
		cell->bold = bold;
		cell->underline = underline;
		cell->fg_color = fg_color;
		cell->bg_color = bg_color;
	}
}

void ushell_write_text( struct USHELL_CLASS *ushell, int x, int y, char *str )
{
	ushell_write_text_full( ushell, x, y, false, false,
		VT100_COLOR_WHITE, VT100_COLOR_RED,
		str, -1
	);
}

void ushell_write_cell_full( struct USHELL_CLASS *ushell, int x, int y, bool bold, bool underline, unsigned char fg_color, unsigned char bg_color, char ch )
{
	struct USHELL_BUFFER_CELL *cell = &ushell->buffer_current[x + y * ushell->w];
	cell->ch = ch;
	cell->bold = bold;
	cell->underline = underline;
	cell->fg_color = fg_color;
	cell->bg_color = bg_color;
}

void ushell_write_cell( struct USHELL_CLASS *ushell, int x, int y, char ch )
{
	ushell_write_cell_full( ushell, x, y, false, false,
		VT100_COLOR_WHITE, VT100_COLOR_RED,
		ch
	);
}

// #############################################################################

void window_write_text_full( struct WINDOW_CLASS *window, int x, int y, bool bold, bool underline, unsigned char fg_color, unsigned char bg_color, char *str, int len )
{
	if( len == -1 )
		len = window->rect.w;
	
	for( int i = 0; str[i] != 0 && i < len; i++ )
	{
		struct USHELL_BUFFER_CELL *cell = &window->paint_buffer[i + x + y * window->rect.w];
		cell->ch = str[i];
		cell->bold = bold;
		cell->underline = underline;
		cell->fg_color = fg_color;
		cell->bg_color = bg_color;
	}
}

void window_write_text( struct WINDOW_CLASS *window, int x, int y, char *str )
{
	window_write_text_full( window, x, y, false, false,
		window->attributes.fg_color, window->attributes.bg_color,
		str, -1
	);
}

void window_write_cell_full( struct WINDOW_CLASS *window, int x, int y, bool bold, bool underline, unsigned char fg_color, unsigned char bg_color, char ch )
{
	struct USHELL_BUFFER_CELL *cell = &window->paint_buffer[x + y * window->rect.w];
	cell->ch = ch;
	cell->bold = bold;
	cell->underline = underline;
	cell->fg_color = fg_color;
	cell->bg_color = bg_color;
}

void window_write_cell( struct WINDOW_CLASS *window, int x, int y, char ch )
{
	window_write_cell_full( window, x, y, false, false,
		window->attributes.fg_color, window->attributes.bg_color,
		ch
	);
}

// #############################################################################

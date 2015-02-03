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

#include "Prompt.h"

// #############################################################################
// global variables
//

// #############################################################################
// functions

void prompt_print( struct WINDOW_CLASS *win, char *str )
{
	struct PROMPT_CLASS *prompt = (struct PROMPT_CLASS *) win->user_def;
	
	GString *log_line = (GString *) g_ptr_array_index( prompt->log_matrix, prompt->log_position );
	g_string_assign( log_line, str );

	// Next line
	prompt->log_position += 1;
	if( prompt->log_position >= prompt->log_size )
		prompt->log_position = 0;
}

// #############################################################################

int prompt_def_wnd_proc( struct WINDOW_CLASS *window, enum WINDOW_MESSAGE command, int uParam, int vParam )
{
	struct PROMPT_CLASS *prompt = (struct PROMPT_CLASS *) window->user_def;
	
	switch( command )
	{
		case WM_CREATE:
		{
			/*prompt->cmd_buffer = g_string_sized_new( 32 );
			prompt->cmd_temp = g_string_sized_new( 32 );
			prompt->cmd_string = g_string_sized_new( 32 );
			prompt->cmd_position = 0;
			prompt->cmd_complete = false;*/
			
			if( prompt->log_size == 0 || prompt->log_size > 32 )
				prompt->log_size = 10;
			prompt->log_position = 0;
			prompt->log_matrix = g_ptr_array_sized_new( prompt->log_size );
			for( int i = 0; i < prompt->log_size; i++ )
			{
				GString *str = g_string_sized_new( 32 );
				//g_string_append_printf( str, "[line %i/%i, str = %04x]", i, prompt->log_matrix->len, str );
				//Serial.println( str->str );
				
				g_ptr_array_add( prompt->log_matrix, str );
			}

			prompt->prompt_len = strlen( prompt->prompt );
			prompt->cursor_position = 0;
			prompt->input_line = g_string_sized_new( 32 );
			
			window->cursor_x = prompt->cursor_position + prompt->prompt_len + 2;
			window->cursor_y = window->rect.h - 2;

			break;
		}
		
		case WM_DESTROY:
		{
			for( int i = 0; i < prompt->log_matrix->len; i++ )
			{
				GString *log_line = (GString *) g_ptr_array_index( prompt->log_matrix, i );
				g_string_free( log_line, true );
			}
			g_ptr_array_free( prompt->log_matrix, true );
			
			g_string_free( prompt->input_line, true );

			break;
		}
		
		case WM_PAINT:
		{
			// Vertical and Horizontal
			for( int i = 0; i < window->rect.w; i++ )
			for( int j = 0; j < window->rect.h; j++ )
			{
				if( j != window->rect.h - 3 )
					window_write_cell( window, i, j, ' ' );
				else
					window_write_cell( window, i, j, 0xC4 /* ─ */ );
			}

			window_write_text( window, 2, window->rect.h - 2, prompt->prompt );
			window_write_text( window, prompt->prompt_len + 2, window->rect.h - 2, prompt->input_line->str );

			// Print log matrix
			for( int i = 0; (i < window->rect.h - 4) && (i < prompt->log_matrix->len); i++ )
			{
				// Get line from log matrix
				GString *log_line = (GString *) g_ptr_array_index(
					prompt->log_matrix,
					(prompt->log_matrix->len - 1 + prompt->log_position - i) % prompt->log_matrix->len
				);
				//Serial.println( String("[i = ") + i + "; x = " + x + "]");
				
				// Clear the line first, then write
				int y = window->rect.h - 4 - i;
				//for( int x = 2; x < window->rect.w - 3; x++ )
				//	window_write_cell( window, x, y, '0' );
				window_write_text( window, 2, y, log_line->str );
			}

			break;
		}

		case WM_CHARACTER:
		{
			char ch = (char) vParam;
			
			switch( ch )
			{
				case 13:	// Enter
				{
					//digitalWrite(13, HIGH);delay(250);digitalWrite(13, LOW);delay(250);	
					
					GString *output = g_string_sized_new( 32 );
					
					g_string_append( output, prompt->prompt );
					g_string_append( output, prompt->input_line->str );
					prompt_print( window, output->str );
					
					g_string_free( output, true );
					
					// Execute the command
					prompt_proccess_cmd( window, prompt->input_line->str );
					
					// Reset input prompt
					g_string_truncate( prompt->input_line, 0 );
					prompt->cursor_position = 0;
					
					break;
				}
				
				default:	// Character
				{
					g_string_append_c( prompt->input_line, ch );
					prompt->cursor_position += 1;

					break;
				}
			}
			
			window->cursor_x = prompt->cursor_position + prompt->prompt_len + 2;
			window_send_message( window, WM_PAINT, 0, 0 );
	
			break;
		}

		case WM_KEY_EVENT:
		{
			
			break;
		}
	}
	
	return window_def_proc( window, command, uParam, vParam );
}

// ############################################################################

void prompt_proccess_cmd( struct WINDOW_CLASS *win, char *cmd_str )
{
	struct PROMPT_CLASS *prompt = (struct PROMPT_CLASS *) win->user_def;

	// Find spacebar
	int cmd_len = strlen( cmd_str );
	int cmd_sp = cmd_len;
	for( int i = 0; cmd_str[i] != 0; i++ )
	{
		if( cmd_str[i] == ' ' )
		{
			cmd_sp = i;
			break;
		}
	}

	if( cmd_sp == 0 )
	{
		// Empty command
		return;
	}

	//p( "cmd_string: %s; cmd_sp: %i\r\n", cmd_string.c_str( ), cmd_sp );

	// Find command in list
	bool cmd_found = false;
	for( int i = 0; prompt->cmd_list[i].cmd != NULL; i++ )
	{
		if( strncmp( prompt->cmd_list[i].cmd, cmd_str, cmd_sp ) == 0 )
		{
			prompt->cmd_list[i].func( &(cmd_str[cmd_sp + 1]) );
			cmd_found = true;
			break;
		}
	}

	if( cmd_found == false )
	{
		// Report command not found
		GString *output = g_string_sized_new( 32 );
		g_string_append( output, "console: command \""  );
		g_string_append( output, cmd_str  );
		g_string_append( output, "\" not found"  );
		prompt_print( win, output->str );
		g_string_free( output, true );
	}
}

// #############################################################################

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

#include "Window_Prompt.h"

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

void prompt_redraw_message( struct WINDOW_CLASS *window )
{
	struct PROMPT_CLASS *prompt = (struct PROMPT_CLASS *) window->user_def;
	
	// Update cursor position on window coordinates
	window->cursor_x = prompt->cursor_position + prompt->prompt_len + 2;
	window_send_message( window, WM_PAINT, 0, 0 );
}

// #############################################################################

int prompt_def_wnd_proc( struct WINDOW_CLASS *window, enum WINDOW_COMMAND command, int uParam, int vParam )
{
	struct PROMPT_CLASS *prompt = (struct PROMPT_CLASS *) window->user_def;
	
	switch( command )
	{
		case WM_CREATE:
		{
			// Prepare log matrix
			if( prompt->log_size == 0 || prompt->log_size > 32 )
				prompt->log_size = 10;
			prompt->log_position = 0;
			prompt->log_matrix = g_ptr_array_sized_new( prompt->log_size );
			for( int i = 0; i < prompt->log_size; i++ )
			{
				GString *str = g_string_sized_new( 32 );
				g_ptr_array_add( prompt->log_matrix, str );
			}

			// Prepare input line buffer
			prompt->prompt_len = strlen( prompt->prompt );
			prompt->cursor_position = 0;
			prompt->input_line = g_string_sized_new( 32 );
			
			// Set cursor position to appropriate place
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

			// Input line
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
				
				// Clear the line first, then write
				window_write_text( window, 2, window->rect.h - 4 - i, log_line->str );
			}

			break;
		}

		case WM_CHARACTER:
		{
			char ch = (char) vParam;
			
			switch( ch )
			{
				case 0x0D:	// Enter
				{
					// Print entered statement to log matrix
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
				
				case 0x7F:	// Backspace
				{
					if( prompt->cursor_position > 0 )
					{
						prompt->cursor_position -= 1;
						g_string_erase( prompt->input_line, prompt->cursor_position, 1 );
					}
					break;
				}
				
				default:	// Character
				{
					g_string_append_c( prompt->input_line, ch );
					prompt->cursor_position += 1;

					break;
				}
			}
		
			prompt_redraw_message( window );
	
			break;
		}

		case WM_KEY_EVENT:
		{
			switch( vParam )
			{
				case VK_LEFT:
				{
					 if( prompt->cursor_position > 0 )
					 {
						 prompt->cursor_position -= 1;
						 Serial.print( "\x1B[D" );	// Move cursor left
					 }

					 break;
				}

				case VK_RIGHT:
				{
					 if( prompt->input_line->len > prompt->cursor_position )
					 {
						 prompt->cursor_position += 1;
						 Serial.print( "\x1B[C" );	// Move cursor left
					 }

					 break;
				}
				
				case VK_DELETE:
				{
					if( prompt->cursor_position < prompt->input_line->len )
					{
						g_string_erase( prompt->input_line, prompt->cursor_position, 1 );
						prompt_redraw_message( window );
					}
					
					break;
				}
			}
			break;
		}
	}
	
	return window_def_proc( window, command, uParam, vParam );
}

// ############################################################################

void prompt_proccess_cmd( struct WINDOW_CLASS *win, char *command_line )
{
	struct PROMPT_CLASS *prompt = (struct PROMPT_CLASS *) win->user_def;

    GSList *token_list = tokenize_command_line( win, command_line );
	if( token_list == NULL )
		return;

	// Find command in list
	char *command_string = (char *) token_list->data;
	for( int i = 0; prompt->command_list[i].cmd != NULL; i++ )
	{
		if( strcmp( prompt->command_list[i].cmd, command_string ) == 0 )
		{
			prompt->command_list[i].func( win, token_list );
			return;
		}
	}

	// Report command not found
	GString *output = g_string_sized_new( 32 );
	g_string_append( output, "prompt: command \""  );
	g_string_append( output, command_string  );
	g_string_append( output, "\" not found"  );
	prompt_print( win, output->str );
	g_string_free( output, true );
}

// #############################################################################
//
// code from gshell.c
//

/* g_parse_argv() does a semi-arbitrary weird subset of the way
 * the shell parses a command line. We don't do variable expansion,
 * don't understand that operators are tokens, don't do tilde expansion,
 * don't do command substitution, no arithmetic expansion, IFS gets ignored,
 * don't do filename globs, don't remove redirection stuff, etc.
 *
 * READ THE UNIX98 SPEC on "Shell Command Language" before changing
 * the behavior of this code.
 *
 * Steps to parsing the argv string:
 *
 *  - tokenize the string (but since we ignore operators,
 *    our tokenization may diverge from what the shell would do)
 *    note that tokenization ignores the internals of a quoted
 *    word and it always splits on spaces, not on IFS even
 *    if we used IFS. We also ignore "end of input indicator"
 *    (I guess this is control-D?)
 *
 *    Tokenization steps, from UNIX98 with operator stuff removed,
 *    are:
 *
 *    1) "If the current character is backslash, single-quote or
 *        double-quote (\, ' or ") and it is not quoted, it will affect
 *        quoting for subsequent characters up to the end of the quoted
 *        text. The rules for quoting are as described in Quoting
 *        . During token recognition no substitutions will be actually
 *        performed, and the result token will contain exactly the
 *        characters that appear in the input (except for newline
 *        character joining), unmodified, including any embedded or
 *        enclosing quotes or substitution operators, between the quote
 *        mark and the end of the quoted text. The token will not be
 *        delimited by the end of the quoted field."
 *
 *    2) "If the current character is an unquoted newline character,
 *        the current token will be delimited."
 *
 *    3) "If the current character is an unquoted blank character, any
 *        token containing the previous character is delimited and the
 *        current character will be discarded."
 *
 *    4) "If the previous character was part of a word, the current
 *        character will be appended to that word."
 *
 *    5) "If the current character is a "#", it and all subsequent
 *        characters up to, but excluding, the next newline character
 *        will be discarded as a comment. The newline character that
 *        ends the line is not considered part of the comment. The
 *        "#" starts a comment only when it is at the beginning of a
 *        token. Since the search for the end-of-comment does not
 *        consider an escaped newline character specially, a comment
 *        cannot be continued to the next line."
 *
 *    6) "The current character will be used as the start of a new word."
 *
 *
 *  - for each token (word), perform portions of word expansion, namely
 *    field splitting (using default whitespace IFS) and quote
 *    removal.  Field splitting may increase the number of words.
 *    Quote removal does not increase the number of words.
 *
 *   "If the complete expansion appropriate for a word results in an
 *   empty field, that empty field will be deleted from the list of
 *   fields that form the completely expanded command, unless the
 *   original word contained single-quote or double-quote characters."
 *    - UNIX98 spec
 *
 *
 */

static inline void ensure_token (GString **token)
{
	if( *token == NULL )
		*token = g_string_new( NULL );
}

static void delimit_token( GString **token, GSList **retval )
{
	if( *token == NULL )
		return;

	*retval = g_slist_prepend( *retval, g_string_free( *token, false ) );

	*token = NULL;
}

static GSList *tokenize_command_line ( struct WINDOW_CLASS *win, const gchar *command_line )
{
	gchar current_quote;
	const gchar *p;
	GString *current_token = NULL;
	GSList *retval = NULL;
	gboolean quoted;

	current_quote = '\0';
	quoted = false;
	p = command_line;

	while( *p )
	{
		if( current_quote == '\\' )
		{
			if( *p == '\n' )
			{
				/* we append nothing; backslash-newline become nothing */
			}
			else
			{
				/* we append the backslash and the current char,
				* to be interpreted later after tokenization
				*/
				ensure_token( &current_token );
				g_string_append_c( current_token, '\\' );
				g_string_append_c( current_token, *p );
			}

			current_quote = '\0';
		}
		else if( current_quote == '#' )
		{
			/* Discard up to and including next newline */
			while( *p && *p != '\n' )
				++p;

			current_quote = '\0';

			if( *p == '\0' )
				break;
		}
		else if( current_quote )
		{
			if( *p == current_quote &&
				/* check that it isn't an escaped double quote */
				!(current_quote == '"' && quoted ) )
			{
				/* close the quote */
				current_quote = '\0';
			}

			/* Everything inside quotes, and the close quote,
			* gets appended literally.
			*/

			ensure_token( &current_token );
			g_string_append_c( current_token, *p );
		}
		else
		{
			switch( *p )
			{
				case '\n':
					delimit_token( &current_token, &retval );
					break;

				case ' ':
				case '\t':
					/* If the current token contains the previous char, delimit
					* the current token. A nonzero length
					* token should always contain the previous char.
					*/
					if( current_token && current_token->len > 0 )
					{
						delimit_token( &current_token, &retval );
					}

					/* discard all unquoted blanks( don't add them to a token ) */
					break;


					/* single/double quotes are appended to the token,
					* escapes are maybe appended next time through the loop,
					* comment chars are never appended.
					*/

				case '\'':
				case '"':
					ensure_token( &current_token );
					g_string_append_c( current_token, *p );

					/* FALL THRU */

				case '#':
				case '\\':
					current_quote = *p;
					break;

				default:
					/* Combines rules 4 ) and 6 ) - if we have a token, append to it,
					* otherwise create a new token.
					*/
					ensure_token( &current_token );
					g_string_append_c( current_token, *p );
				break;
			}
		}

		/* We need to count consecutive backslashes mod 2,
		* to detect escaped doublequotes.
		*/
		if( *p != '\\' )
			quoted = false;
		else
			quoted = !quoted;

		++p;
	}

	delimit_token( &current_token, &retval );

	GString *error_msg = NULL;

	if( current_quote )
	{
		error_msg = g_string_sized_new( 32 );

		if( current_quote == '\\' )
		{
			g_string_append( error_msg, "tokenize_command_line: Text ended just after a '\\' character." );
		}
		else
		{
			g_string_append( error_msg, "Text ended before matching quote was found for " );
			g_string_append_c( error_msg, current_quote );
			g_string_append( error_msg, "." );
		}

		goto error;
	}

	if( retval == NULL )
	{
		error_msg = g_string_sized_new( 32 );
		g_string_append( error_msg, "Text was empty (or contained only whitespace)" );

		goto error;
	}

	/* we appended backward */
	retval = g_slist_reverse( retval );

	return retval;

error:

	if( error_msg != NULL )
	{
		prompt_print( win, error_msg->str );
		g_string_free( error_msg, true );
	}

	//g_assert( error == NULL || *error != NULL );

	g_slist_free_full( retval, g_free );

	return NULL;
}

// #############################################################################

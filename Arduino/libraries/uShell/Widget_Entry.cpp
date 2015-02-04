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

#include "Widget_Entry.h"

// #############################################################################
// global variables
//

// #############################################################################
// functions

void entry_set_text( struct WINDOW_CLASS *window, char *text )
{
	struct ENTRY_CLASS *entry = (struct ENTRY_CLASS *) window->user_def;
	g_string_assign( entry->text, text );
	
	window_send_message( window, WM_PAINT, 0, 0 );
}

// #############################################################################

int entry_def_wnd_proc( struct WINDOW_CLASS *window, enum WINDOW_COMMAND command, int uParam, int vParam )
{
	struct ENTRY_CLASS *entry = (struct ENTRY_CLASS *) window->user_def;
	
	switch( command )
	{
		case WM_CREATE:
		{
			entry->text = g_string_sized_new( 32 );

			break;
		}
		
		case WM_DESTROY:
		{


			break;
		}
		
		case WM_PAINT:
		{
			//           11111111112
			// 012345678901234567890
			// label:      [ text  ]
			//
			// label_len = 6
			// label_width = 12
			// window->w = 21
			
			//
			// Print label if alignment is specified
			//

			int label_len = strlen( window->title );
			if( label_len > entry->label_width )
				label_len = entry->label_width;
			if( entry->label_align == ENTRY_LABEL_LEFT )
			{
				for( int i = 0; i < label_len ; i++ )
					window_write_cell( window, i, 0, window->title[i] );
			}
			else if( entry->label_align == ENTRY_LABEL_RIGHT )
			{
				for( int i = window->rect.w; i != 0 && label_len - 1 - i > 1; i-- )
					window_write_cell( window, i, 0, window->title[label_len - 1 - i] );
			}

			window_write_cell( window, entry->label_width, 0, '[' );
			window_write_cell( window, window->rect.w - 1, 0, ']' );
			window_write_text( window, entry->label_width + 2, 0, entry->text->str );

			break;
		}

		case WM_CHARACTER:
		{
			char ch = (char) vParam;

			break;
		}

		case WM_KEY_EVENT:
		{
			switch( vParam )
			{
				case VK_LEFT:
				{


					 break;
				}

				case VK_RIGHT:
				{


					 break;
				}
				
				case VK_DELETE:
				{

					
					break;
				}
			}
			break;
		}
	}
	
	return window_def_proc( window, command, uParam, vParam );
}

// #############################################################################

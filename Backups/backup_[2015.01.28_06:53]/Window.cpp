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

#include "Window.h"

// #############################################################################
// global variables
//

// #############################################################################
// functions

struct WINDOW_CLASS *window_create(
	struct USHELL_CLASS *ushell,
	const char *title,
	struct WINDOW_ATTRIBUTES *attributes,
	struct WINDOW_RECT *rect,
	int (*wnd_proc) ( struct WINDOW_CLASS *window, enum WINDOW_MESSAGE command, int uParam, int vParam ),
	void *user_def
)
{
	//
	// Memory allocation and variable copying
	//
	
	struct WINDOW_CLASS *win = (struct WINDOW_CLASS *) malloc( sizeof(struct WINDOW_CLASS) );
	
	win->title = (char *) title;

	memcpy( &win->attributes, attributes, sizeof(struct WINDOW_ATTRIBUTES) );
	memcpy( &win->rect, rect, sizeof(struct WINDOW_RECT) );

	size_t buffer_size = win->rect.w * win->rect.h * sizeof(struct CONSOLE_BUFFER_CELL);
	win->paint_buffer = (struct CONSOLE_BUFFER_CELL *) malloc( buffer_size );
	memset( win->paint_buffer, 0, buffer_size );

	win->wnd_proc = wnd_proc;
	
	win->user_def = user_def;
	
	win->ushell = ushell;
	win->console = ushell->console;
	
	//
	// Make window appear on the console
	//
	
	window_send_message( win, WM_CREATE, 0, 0 );
	window_send_message( win, WM_PAINT, 0, 0 );
	
	return win;
}

// #############################################################################

int window_send_message( struct WINDOW_CLASS *window, enum WINDOW_MESSAGE command, int uParam, int vParam )
{
	if( window->wnd_proc != NULL )
		window->wnd_proc( window, command, uParam, vParam );
}

// #############################################################################

int window_def_proc( struct WINDOW_CLASS *window, enum WINDOW_MESSAGE command, int uParam, int vParam )
{
	switch( command )
	{

		case WM_PAINT:
		{
			int title_len = strlen( window->title );
			
			for( int j = 0; j < window->rect.h; j++ )
			for( int i = 0; i < window->rect.w; i++ )
			{
				struct CONSOLE_BUFFER_CELL *cell = &window->paint_buffer[i + j * window->rect.w];
				
				// Corners
				if( i == 0 && j == 0 )
					cell->ch = '+'; // Left-top
				else if( i == 0 && j == window->rect.w - 1 )
					cell->ch = '+'; // Left-bottom
				else if( i == window->rect.h - 1 && j == 0 )
					cell->ch = '+'; // Right-top
				else if( i == window->rect.h - 1 && j == window->rect.w - 1 )
					cell->ch = '+'; // Right-bottom
				else if( i == 0 || i == window->rect.h - 1 )
					cell->ch = '|'; // Horizontal
				else if( j == 0 || j == window->rect.w - 1 )
					cell->ch = '-'; // Vertical
				
				// Title
				char title_offset = 3;
				if( i > title_offset && j == 0 &&
					(i - title_offset >= 0 && i - title_offset < title_len )
				)
					cell->ch = window->title[i - title_offset];
				
				cell->fg_color = window->attributes.fg_color;
				cell->bg_color = window->attributes.bg_color;
			}
			
			console_copy_rect( window->console, window->paint_buffer, window->rect.x, window->rect.y, window->rect.w, window->rect.h );
			console_swap_buffers( window->console );
			
			break;
		}
		
	}
	
	return 0;
}

// #############################################################################

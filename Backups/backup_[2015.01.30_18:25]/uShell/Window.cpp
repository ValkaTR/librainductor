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
	for( int j = 0; j < win->rect.h; j++ )
	for( int i = 0; i < win->rect.w; i++ )
		window_write_cell( win, i, j, '0' );

	win->wnd_proc = wnd_proc;
	
	win->user_def = user_def;
	
	win->ushell = ushell;
	win->console = ushell->console;
	
	//
	// Make window appear on the console
	//
	
	g_ptr_array_add( ushell->window_list, win );
	
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

struct WINDOW_CLASS *window_get_active( struct USHELL_CLASS *ushell )
{
	if( ushell->window_list->len != 0 )
		return (struct WINDOW_CLASS *) g_ptr_array_index( ushell->window_list, ushell->window_list->len - 1 );
	else
		return NULL;
}

// #############################################################################

void window_write_text( struct WINDOW_CLASS *window, int x, int y, char *str )
{
	for( int i = 0; str[i] != 0; i++ )
	{
		struct CONSOLE_BUFFER_CELL *cell = &window->paint_buffer[i + x + y * window->rect.w];
		cell->ch = str[i];
		cell->fg_color = window->attributes.fg_color;
		cell->bg_color = window->attributes.bg_color;
	}
}

void window_write_cell( struct WINDOW_CLASS *window, int x, int y, char ch )
{
	struct CONSOLE_BUFFER_CELL *cell = &window->paint_buffer[x + y * window->rect.w];
	cell->ch = ch;
	cell->fg_color = window->attributes.fg_color;
	cell->bg_color = window->attributes.bg_color;
}

// #############################################################################

int window_def_proc( struct WINDOW_CLASS *window, enum WINDOW_MESSAGE command, int uParam, int vParam )
{
	switch( command )
	{

		case WM_PAINT:
		{
			// Vertical and Horizontal
			for( int i = 0; i < window->rect.w; i++ ) window_write_cell( window, i, 0, 0xCD /* ═ */ );
			for( int i = 0; i < window->rect.w; i++ ) window_write_cell( window, i, window->rect.h - 1, 0xCD /* ═ */ );
			for( int j = 0; j < window->rect.h; j++ ) window_write_cell( window, 0, j, 0xBA /* ║ */ );
			for( int j = 0; j < window->rect.h; j++ ) window_write_cell( window, window->rect.w - 1, j, 0xBA /* ║ */ );
			
			// Corners
			window_write_cell( window, 0, 0, 0xC9 /* ╔ */ );
			window_write_cell( window, 0, window->rect.h - 1, 0xC8 /* ╚ */ );
			window_write_cell( window, window->rect.w - 1, 0, 0xBB /* ╗ */ );
			window_write_cell( window, window->rect.w - 1, window->rect.h - 1, 0xBC /* ╝ */ );

			// Shadow
			//for( int i = 1; i < window->rect.w + 1; i++ ) window_write_cell( window, i, window->rect.h, 0xB0 /* ░ */ );
			//for( int j = 1; j < window->rect.h + 1; j++ ) window_write_cell( window, window->rect.w, j, 0xB0 /* ░ */ );
			
			// Title
			int title_len = strlen( window->title );
			char title_offset = 4;
			for( int i = 0; i < title_len; i++ ) window_write_cell( window, i + title_offset, 0, window->title[i] );
			window_write_cell( window, title_offset - 2, 0, '[' );
			window_write_cell( window, title_offset - 1, 0, ' ' );
			window_write_cell( window, title_offset + title_len, 0, ' ' );
			window_write_cell( window, title_offset + title_len + 1, 0, ']' );
			
			window->paint_buffer[75 + 1 * window->rect.w].ch = '1';
			window->paint_buffer[75 + 1 * window->rect.w].fg_color = 1;
			
			console_copy_rect( window->console, window->paint_buffer, window->rect.x, window->rect.y, window->rect.w, window->rect.h );
			console_swap_buffers( window->console );
			
			break;
		}
		
	}
	
	return 0;
}

// #############################################################################

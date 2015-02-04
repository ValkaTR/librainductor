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
	struct WINDOW_CLASS *parent,
	const char *title,
	struct WINDOW_ATTRIBUTES *attributes,
	struct WINDOW_RECT *rect,
	int (*wnd_proc) ( struct WINDOW_CLASS *window, enum WINDOW_COMMAND command, int uParam, int vParam ),
	void *user_def
)
{
	//
	// Memory allocation and variable copying
	//
	
	struct WINDOW_CLASS *window = (struct WINDOW_CLASS *) malloc( sizeof(struct WINDOW_CLASS) );
	
	window->title = (char *) title;

	memcpy( &window->attributes, attributes, sizeof(struct WINDOW_ATTRIBUTES) );
	memcpy( &window->rect, rect, sizeof(struct WINDOW_RECT) );

	size_t buffer_size = window->rect.w * window->rect.h * sizeof(struct CONSOLE_BUFFER_CELL);
	window->paint_buffer = (struct CONSOLE_BUFFER_CELL *) malloc( buffer_size );
	memset( window->paint_buffer, 0, buffer_size );
	for( int j = 0; j < window->rect.h; j++ )
	for( int i = 0; i < window->rect.w; i++ )
		window_write_cell( window, i, j, ' ' );

	window->wnd_proc = wnd_proc;	
	window->user_def = user_def;

	window->ushell = ushell;
	window->console = ushell->console;

	window->widgets = g_ptr_array_new( );
	if( parent != NULL )
	{
		window->parent = parent;
		g_ptr_array_add( parent->widgets, window );
	}
	else
	{
		// If there's no parent window, then attach this
		// to the root
		g_ptr_array_add( ushell->window_list, window );
	}
	
	//
	// Make window appear on the console
	//

	window_send_message( window, WM_CREATE, 0, 0 );
	window_send_message( window, WM_PAINT, 0, 0 );
	
	return window;
}

// #############################################################################

int window_send_message( struct WINDOW_CLASS *window, enum WINDOW_COMMAND command, int uParam, int vParam )
{
	struct WINDOW_MESSAGE msg =
	{
		.window = window,
		.command = command,
		.uParam = uParam,
		.vParam = vParam
	};
	
	ushell_add_message( window->ushell, &msg );
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

void window_write_text_full( struct WINDOW_CLASS *window, int x, int y, bool bold, bool underline, unsigned char fg_color, unsigned char bg_color, char *str )
{
	for( int i = 0; str[i] != 0; i++ )
	{
		struct CONSOLE_BUFFER_CELL *cell = &window->paint_buffer[i + x + y * window->rect.w];
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
		str
	);
}

void window_write_cell_full( struct WINDOW_CLASS *window, int x, int y, bool bold, bool underline, unsigned char fg_color, unsigned char bg_color, char ch )
{
	struct CONSOLE_BUFFER_CELL *cell = &window->paint_buffer[x + y * window->rect.w];
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

int window_def_proc( struct WINDOW_CLASS *window, enum WINDOW_COMMAND command, int uParam, int vParam )
{
	switch( command )
	{
		case WM_PAINT:
		{
			if( window->attributes.border_style == WINDOW_BORDER_DOUBLE )
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
			}
			else if( window->attributes.border_style == WINDOW_BORDER_SINGLE )
			{
				// Vertical and Horizontal
				for( int i = 0; i < window->rect.w; i++ ) window_write_cell( window, i, 0, 0xC4 /* ─ */ );
				for( int i = 0; i < window->rect.w; i++ ) window_write_cell( window, i, window->rect.h - 1, 0xC4 /* ─ */ );
				for( int j = 0; j < window->rect.h; j++ ) window_write_cell( window, 0, j, 0xB3 /* │ */ );
				for( int j = 0; j < window->rect.h; j++ ) window_write_cell( window, window->rect.w - 1, j, 0xB3 /* │ */ );
				
				// Corners
				window_write_cell( window, 0, 0, 0xDA /* ┌ */ );
				window_write_cell( window, 0, window->rect.h - 1, 0xC0 /* └ */ );
				window_write_cell( window, window->rect.w - 1, 0, 0xBF /* ┐ */ );
				window_write_cell( window, window->rect.w - 1, window->rect.h - 1, 0xD9 /* ┘ */ );
			}

			// Shadow
			//for( int i = 1; i < window->rect.w + 1; i++ ) window_write_cell( window, i, window->rect.h, 0xB0 /* ░ */ );
			//for( int j = 1; j < window->rect.h + 1; j++ ) window_write_cell( window, window->rect.w, j, 0xB0 /* ░ */ );
			// Title
			if( window->attributes.border_style != WINDOW_BORDER_NONE )
			{
				int title_len = strlen( window->title );
				char title_offset = 4;
				for( int i = 0; i < title_len; i++ ) window_write_cell( window, i + title_offset, 0, window->title[i] );
				window_write_cell( window, title_offset - 2, 0, '[' );
				window_write_cell( window, title_offset - 1, 0, ' ' );
				window_write_cell( window, title_offset + title_len, 0, ' ' );
				window_write_cell( window, title_offset + title_len + 1, 0, ']' );
			}
			
			// Draw all widgets
			if( window->widgets != NULL && window->widgets->len > 0 )
			{
				for( int i = 0; window->widgets->len < i; i++ )
				{
					struct WINDOW_CLASS *widget = (struct WINDOW_CLASS *) (window->widgets->pdata[i]);
					window_send_message( widget, WM_PAINT, 0, 0 );
				}
			}

			console_copy_rect( window->console, window->paint_buffer, window->rect.x, window->rect.y, window->rect.w, window->rect.h );
			console_swap_buffers( window->console );
			
			break;
		}
		
	}
	
	return 0;
}

// #############################################################################

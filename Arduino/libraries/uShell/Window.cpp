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

	window->widget_list = g_ptr_array_new( );
	if( parent != NULL )
	{
		window->parent = parent;
		g_ptr_array_add( parent->widget_list, window );
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
			// Draw all widgets
			if( window->widget_list != NULL && window->widget_list->len > 0 )
			{
				for( int i = 0; window->widget_list->len < i; i++ )
				{
					struct WINDOW_CLASS *widget = (struct WINDOW_CLASS *) (window->widget_list->pdata[i]);
					window_send_message( widget, WM_PAINT, 0, 0 );
				}
			}

			if( window->parent == NULL )
			{
				console_copy_rect( window->console->buffer_current, window->paint_buffer, window->rect.x, window->rect.y, window->rect.w, window->rect.h );
				console_swap_buffers( window->console );
			}
			else
			{
				console_copy_rect( window->parent->paint_buffer, window->paint_buffer, window->rect.x, window->rect.y, window->rect.w, window->rect.h );
			}
			
			break;
		}

		case WM_CHARACTER:
		{
			char ch = (char) vParam;
			/*Serial.print( "[character, " );
			Serial.print( uParam );
			Serial.print( ", " );
			Serial.print( vParam );
			Serial.println( "]" );*/

			switch( ch )
			{
				case 14:	// Ctrl+N
				{
					window->active_widget += 1;
					if( window->active_widget == window->widget_list->len - 1 )
						window->active_widget = 0;
					window_send_message( window, WM_PAINT, 0, 0 );
					break;
				}
				
				case 16:	// Ctrl+P
				{
					window->active_widget -= 1;
					if( window->active_widget == -1 )
						window->active_widget = window->widget_list->len - 1;
					window_send_message( window, WM_PAINT, 0, 0 );
					break;
				}
			}
			Serial.print( "[active_window_id, " );
			Serial.print( window->active_widget );
			Serial.println( ", " );
			Serial.print( window->widget_list->len );
			Serial.println( "]" );
			break;
	}
	
	return 0;
}

// #############################################################################

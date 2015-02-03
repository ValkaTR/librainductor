// #############################################################################
//
//
//
// #############################################################################

#ifndef __window_h__
#define __window_h__

// #############################################################################
// includes of system headers
//

#include <Arduino.h>

// #############################################################################
// includes of local headers
//

#include "uShell.h"
#include "Window.h"
#include "Console.h"
#include "garray.h"

// #############################################################################
// type and constant definitions
//

// #############################################################################
// class declarations
//

enum WINDOW_MESSAGE
{
	WM_CREATE = 1,
	WM_DESTROY,
	WM_PAINT,
	WM_KEY_EVENT,
	WM_CHARACTER
};

struct WINDOW_RECT
{
	int x; int y;
	int w; int h;
};

enum WINDOW_BORDER_STYLE
{
	WINDOW_BORDER_NONE = 0,
	WINDOW_BORDER_SINGLE,
	WINDOW_BORDER_DOUBLE
};

struct WINDOW_ATTRIBUTES
{
	char fg_color;
	char bg_color;
	
	enum WINDOW_BORDER_STYLE border_style;
};

struct WINDOW_CLASS
{
	char *title;
	
	struct WINDOW_ATTRIBUTES attributes;
	struct WINDOW_RECT rect;
	
	struct CONSOLE_BUFFER_CELL *paint_buffer;
	
	int (*wnd_proc) ( struct WINDOW_CLASS *window, enum WINDOW_MESSAGE command, int uParam, int vParam );

	int cursor_x;
	int cursor_y;

	// User defined variable to distinguish different windows in a single wnd_proc
	void *user_def;

	// Feedback
	struct USHELL_CLASS *ushell;
	struct CONSOLE_CLASS *console;
};

// #############################################################################
// function declarations
//

struct WINDOW_CLASS *window_create(
	struct USHELL_CLASS *ushell,
	const char *title,
	struct WINDOW_ATTRIBUTES *attributes,
	struct WINDOW_RECT *rect,
	int (*wnd_proc) ( struct WINDOW_CLASS *window, enum WINDOW_MESSAGE command, int uParam, int vParam ),
	void *user_def
);
	
int window_send_message( struct WINDOW_CLASS *window, enum WINDOW_MESSAGE command, int uParam, int vParam );
struct WINDOW_CLASS *window_get_active( struct USHELL_CLASS *ushell );
void window_write_cell( struct WINDOW_CLASS *window, int x, int y, char ch );
void window_write_text( struct WINDOW_CLASS *window, int x, int y, char *str );

int window_def_proc( struct WINDOW_CLASS *window, enum WINDOW_MESSAGE command, int uParam, int vParam );

// #############################################################################

#endif // __window_h__

// #############################################################################



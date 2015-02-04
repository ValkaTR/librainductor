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
#include "Console.h"
#include "garray.h"

G_BEGIN_DECLS

// #############################################################################
// type and constant definitions
//

// #############################################################################
// class declarations
//

//
// Messages
//

enum WINDOW_COMMAND
{
	WM_CREATE = 1,
	WM_DESTROY,
	WM_PAINT,
	WM_KEY_EVENT,
	WM_CHARACTER,
	WM_SERIAL_EVENT
};

struct WINDOW_MESSAGE
{
	struct WINDOW_CLASS *window;
	enum WINDOW_COMMAND command;
	int uParam;
	int vParam;
};

//
// Window attributes
//

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

//
// Main window class
//

struct WINDOW_CLASS
{
	char *title;
	
	struct WINDOW_ATTRIBUTES attributes;
	struct WINDOW_RECT rect;
	
	struct CONSOLE_BUFFER_CELL *paint_buffer;

	GPtrArray *widgets;
	
	int (*wnd_proc) ( struct WINDOW_CLASS *window, enum WINDOW_COMMAND command, int uParam, int vParam );

	int cursor_x;
	int cursor_y;

	// User defined variable to distinguish different windows in a single wnd_proc
	void *user_def;

	// Feedback
	struct WINDOW_CLASS *parent;
	struct USHELL_CLASS *ushell;
	struct CONSOLE_CLASS *console;
};

// #############################################################################
// function declarations
//

struct WINDOW_CLASS *window_create(
	struct USHELL_CLASS *ushell,
	struct WINDOW_CLASS *parent,
	const char *title,
	struct WINDOW_ATTRIBUTES *attributes,
	struct WINDOW_RECT *rect,
	int (*wnd_proc) ( struct WINDOW_CLASS *window, enum WINDOW_COMMAND command, int uParam, int vParam ),
	void *user_def
);
	
int window_send_message( struct WINDOW_CLASS *window, enum WINDOW_COMMAND command, int uParam, int vParam );
struct WINDOW_CLASS *window_get_active( struct USHELL_CLASS *ushell );
void window_write_text_full( struct WINDOW_CLASS *window, int x, int y, bool bold, bool underline, unsigned char fg_color, unsigned char bg_color, char *str );
void window_write_text( struct WINDOW_CLASS *window, int x, int y, char *str );
void window_write_cell_full( struct WINDOW_CLASS *window, int x, int y, bool bold, bool underline, unsigned char fg_color, unsigned char bg_color, char ch );
void window_write_cell( struct WINDOW_CLASS *window, int x, int y, char ch );

int window_def_proc( struct WINDOW_CLASS *window, enum WINDOW_COMMAND command, int uParam, int vParam );

// #############################################################################

G_END_DECLS

#endif // __window_h__

// #############################################################################



// #############################################################################
//
//
//
// #############################################################################

#ifndef __ushell_h__
#define __ushell_h__

// #############################################################################
// includes of system headers
//

#include <Arduino.h>

// #############################################################################
// includes of local headers
//

#include "Console.h"
#include "gstring.h"

// #############################################################################
// type and constant definitions
//

// #############################################################################
// class declarations
//

enum USHELL_COMMANDS
{
	WINDOW_CREATE = 1,
	WINDOW_DESTROY,
	WINDOW_PAINT,
	WINDOW_KEY_EVENT,
	WINDOW_CHARACTER
};

struct USHELL_WINDOW_ATTRIBUTES
{
	unsigned char fg_color;
	unsigned char bg_color;
};

struct USHELL_WINDOW
{
	int x, y;
	int w, h;
	
	struct USHELL_WINDOW_ATTRIBUTES attributes;
	
	int (*callback_proc) ( struct USHELL_WINDOW *window, int command, int uParam, int vParam );
	
	void *user_def;
};

struct USHELL
{
	//void (*print_callback) ( char *str, void *user_def );
	//void *print_user_def;
char padding1[32];
	//
	// Key event proccessing variables
	//
	
	char cmd_escape_len;char padding2[32];
	char cmd_prev_ch;
	GString *cmd_esc_buf;        // a string for escape control codes
	GString *cmd_number;
	enum XTERM_CONTROL_CHARACTER cmd_control_character;

	struct KEY_EVENT_MODIFIERS mods;
	
	//
	// Double buffering console
	//
	
	struct USHELL_CONSOLE *console;
	UARTClass *uart_port;
	
	//
	// Interface variables
	//
	
	struct USHELL_WINDOW *window_list;
	int window_count;
};

// #############################################################################
// function declarations
//

struct USHELL *ushell_init( char *prompt, struct CONSOLE_COMMAND *cmd_list, void (*proccess_print) ( char *, void * ), void *user_def );

void ushell_proccess_loop( struct USHELL *ushell );
void ushell_proccess_event( struct USHELL *ushell, char ch );
void ushell_proccess_print( struct USHELL *ushell, char *str );

struct USHELL_WINDOW *ushell_create_window( int x, int y, int w, int h, struct USHELL_WINDOW_ATTRIBUTES *attributes, int (*callback_proc) (struct USHELL_WINDOW *window, int command, int uParam, int vParam ) );
int ushell_send_command( struct USHELL_WINDOW *window, int command, int uParam, int vParam );

//
// Key event proccessing
//

void ushell_proccess_char( struct USHELL *ushell, char ch );
void ushell_proccess_escape( struct USHELL *ushell, char ch );
void ushell_proccess_key( struct USHELL *ushell, char ch, struct KEY_EVENT_MODIFIERS mod, int code );
void ushell_prompt_reset(struct USHELL *ushell );
void ushell_escape_end( struct USHELL *ushell );

//void reprint_line( );

// #############################################################################

#endif // __ushell_h__

// #############################################################################


// #############################################################################
//
//
//
// #############################################################################

#ifndef __prompt_h__
#define __prompt_h__

// #############################################################################
// includes of system headers
//

#include <Arduino.h>

// #############################################################################
// includes of local headers
//

#include "uShell.h"

G_BEGIN_DECLS

// #############################################################################
// type and constant definitions
//

// #############################################################################
// class declarations
//

struct PROMPT_COMMAND
{
	char *cmd;	// Command name
	void (*func)(struct WINDOW_CLASS *, GSList *);	// Callback function
};

struct PROMPT_CLASS
{
	struct PROMPT_COMMAND *command_list;

	char *prompt;
	int prompt_len;

	GPtrArray *log_matrix;		// Matrix-like Log buffer
	int log_position;
	int log_size;
	
	GString *input_line;		// Input text
	int cursor_position;
};

// #############################################################################
// function declarations
//

struct WINDOW_CLASS *prompt_create( struct USHELL_CLASS *ushell, struct PROMPT_COMMAND *command_list, int x, int y, int w, int h );

void prompt_print( struct WINDOW_CLASS *win, char *str );

bool prompt_create_proc( struct WINDOW_CLASS *window, struct WINDOW_GENERIC_MESSAGE *msg, void *user_def );
bool prompt_destroy_proc( struct WINDOW_CLASS *window, struct WINDOW_GENERIC_MESSAGE *msg, void *user_def );
bool prompt_paint_proc( struct WINDOW_CLASS *window, struct WINDOW_PAINT_MESSAGE *msg, void *user_def );
bool prompt_key_event_proc( struct WINDOW_CLASS *window, struct WINDOW_KEY_EVENT_MESSAGE *msg, void *user_def );
bool prompt_character_proc( struct WINDOW_CLASS *window, struct WINDOW_CHARACTER_MESSAGE *msg, void *user_def );

void prompt_proccess_cmd( struct WINDOW_CLASS *win, char *command_line );
static GSList *tokenize_command_line( struct WINDOW_CLASS *win, const gchar *command_line );

// #############################################################################

G_END_DECLS

#endif // __prompt_h__

// #############################################################################



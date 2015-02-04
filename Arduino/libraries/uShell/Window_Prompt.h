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

#include "Window.h"
#include "gslist.h"
#include "garray.h"

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

void prompt_print( struct WINDOW_CLASS *win, char *str );

int prompt_def_wnd_proc( struct WINDOW_CLASS *window, enum WINDOW_COMMAND command, int uParam, int vParam );

void prompt_proccess_cmd( struct WINDOW_CLASS *win, char *command_line );
static GSList *tokenize_command_line( struct WINDOW_CLASS *win, const gchar *command_line );

// #############################################################################

G_END_DECLS

#endif // __prompt_h__

// #############################################################################



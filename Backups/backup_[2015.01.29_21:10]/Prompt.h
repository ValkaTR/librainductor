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
#include "garray.h"

// #############################################################################
// type and constant definitions
//

// #############################################################################
// class declarations
//

struct PROMPT_COMMAND
{
	char *cmd;	// Command name
	void (*func)(char *);	// Callback function
};

struct PROMPT_CLASS
{
	struct PROMPT_COMMAND *cmd_list;

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

int prompt_def_wnd_proc( struct WINDOW_CLASS *window, enum WINDOW_MESSAGE command, int uParam, int vParam );

void prompt_proccess_cmd( struct WINDOW_CLASS *win, char *str );

// #############################################################################

#endif // __prompt_h__

// #############################################################################



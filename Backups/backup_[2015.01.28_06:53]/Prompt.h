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

// #############################################################################
// type and constant definitions
//

// #############################################################################
// class declarations
//

struct USHELL_PROMPT
{
	struct CONSOLE_COMMAND *cmd_list;

	char *prompt;

	String cmd_buffer;         // a string to hold incoming data
	String cmd_temp;           // temp buffer
	String cmd_string;         // a string to proccess cmds
	String cmd_number;         // a string to control numbers
	signed int cmd_pos;
	boolean cmd_complete;      // whether the string is complete
};

// #############################################################################
// function declarations
//

struct USHELL_CLASS *prompt_callback( struct USHELL_WINDOW *window, int command, int uParam, int vParam );

int prompt_def_wnd_proc( struct WINDOW_CLASS *window, enum WINDOW_MESSAGE command, int uParam, int vParam );

// #############################################################################

#endif // __prompt_h__

// #############################################################################



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

#include "uShell.h"

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

struct USHELL *prompt_callback( struct USHELL_WINDOW *window, int command, int uParam, int vParam );

// #############################################################################

#endif // __ushell_h__

// #############################################################################



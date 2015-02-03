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

#include "Prompt.h"

// #############################################################################
// global variables
//

// #############################################################################
// functions

int prompt_def_wnd_proc( struct WINDOW_CLASS *window, enum WINDOW_MESSAGE command, int uParam, int vParam )
{
	switch( command )
	{
		case WM_CREATE:
		{
			
			
			break;
		}
		
		case WM_PAINT:
		{
			
			
			break;
		}
		
	}
	
	return window_def_proc( window, command, uParam, vParam );
}

// #############################################################################

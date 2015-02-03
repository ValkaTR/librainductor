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

#include "GPIO.h"

// #############################################################################
// global variables
//

// #############################################################################
// functions

int gpio_def_wnd_proc( struct WINDOW_CLASS *window, enum WINDOW_MESSAGE command, int uParam, int vParam )
{
	struct GPIO_CLASS *gpio = (struct GPIO_CLASS *) window->user_def;
	
	switch( command )
	{
		case WM_CREATE:
		{


			break;
		}
		
		case WM_DESTROY:
		{


			break;
		}
		
		case WM_PAINT:
		{


			break;
		}

		case WM_CHARACTER:
		{
			char ch = (char) vParam;

			break;
		}

		case WM_KEY_EVENT:
		{
			switch( vParam )
			{
				case VK_LEFT:
				{


					 break;
				}

				case VK_RIGHT:
				{


					 break;
				}
				
				case VK_DELETE:
				{

					
					break;
				}
			}
			break;
		}
	}
	
	return window_def_proc( window, command, uParam, vParam );
}

// #############################################################################

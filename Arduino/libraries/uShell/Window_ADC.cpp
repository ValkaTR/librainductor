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

#include "Window_ADC.h"

// #############################################################################
// global variables
//

//
//    00000000001111111111222222222233333333334444444444555555555566666666667777777777
// \x 01234567890123456789012345678901234567890123456789012345678901234567890123456789
// y  ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
// 0  ╔═[ ADC ]══════════════════════════════════════════════════════════════════════╗
// 1  ║                                                                              ║
// 2  ║ A0: [###########-----] 75%            A6: [###########-----] 75%             ║
// 2  ║ A1: [###########-----] 75%            A7: [###########-----] 75%             ║
// 2  ║ A2: [###########-----] 75%            A8: [###########-----] 75%             ║
// 2  ║ A3: [###########-----] 75%            A9: [###########-----] 75%             ║
// 2  ║ A4: [###########-----] 75%           A10: [###########-----] 75%             ║
// 2  ║ A5: [###########-----] 75%           A11: [###########-----] 75%             ║
// 3  ║                                                                              ║
// 9  ╚══════════════════════════════════════════════════════════════════════════════╝
//    ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
//

// #############################################################################
// functions
//

int adc_def_wnd_proc( struct WINDOW_CLASS *window, enum WINDOW_MESSAGE command, int uParam, int vParam )
{
	struct GPIO_CLASS *adc = (struct GPIO_CLASS *) window->user_def;
	
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
			for( int j = 1; j < window->rect.h - 1; j++ )
			for( int i = 1; i < window->rect.w - 1; i++ )
			window_write_text_full( window, i, j, false, false, VT100_COLOR_DEFAULT, VT100_COLOR_DEFAULT, " " );
			
			for( int j = 1; j < 10 + 1; j++ )
			window_write_cell_full( window, 68, j, false, false, VT100_COLOR_DEFAULT, VT100_COLOR_DEFAULT, 0xB3 );
			
			window_write_text_full( window, 2, 2, false, false, VT100_COLOR_DEFAULT, VT100_COLOR_DEFAULT, "PA" );
			window_write_text_full( window, 2, 4, false, false, VT100_COLOR_DEFAULT, VT100_COLOR_DEFAULT, "PB" );
			window_write_text_full( window, 2, 6, false, false, VT100_COLOR_DEFAULT, VT100_COLOR_DEFAULT, "PC" );
			window_write_text_full( window, 2, 8, false, false, VT100_COLOR_DEFAULT, VT100_COLOR_DEFAULT, "PD" );
			
			window_write_text_full( window, 70, 1, false, false, VT100_COLOR_DEFAULT, VT100_COLOR_DEFAULT, "LEGEND" );
			window_write_cell_full( window, 74, 3, false, false, VT100_COLOR_DEFAULT, VT100_COLOR_DEFAULT, '0' );
			window_write_cell_full( window, 76, 3, false, false, VT100_COLOR_DEFAULT, VT100_COLOR_DEFAULT, '1' );
			window_write_text_full( window, 71, 5, false, false, VT100_COLOR_DEFAULT, VT100_COLOR_DEFAULT, "IN" );
			window_write_cell_full( window, 74, 5, false, false, VT100_COLOR_BLACK, VT100_COLOR_BLUE, 0xF9 );
			window_write_cell_full( window, 76, 5, false, false, VT100_COLOR_WHITE, VT100_COLOR_BLUE, 0xF9 );
			window_write_text_full( window, 70, 7, false, false, VT100_COLOR_DEFAULT, VT100_COLOR_DEFAULT, "OUT" );
			window_write_cell_full( window, 74, 7, false, false, VT100_COLOR_BLACK, VT100_COLOR_RED, 0xF9 );
			window_write_cell_full( window, 76, 7, false, false, VT100_COLOR_WHITE, VT100_COLOR_RED, 0xF9 );


uint32_t ulPin = 13;
PIO_GetOutputDataStatus( g_APinDescription[ulPin].pPort, g_APinDescription[ulPin].ulPin );
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

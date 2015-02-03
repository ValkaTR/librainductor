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

#include "Window_GPIO.h"
#include "Widget_Entry.h"

// #############################################################################
// global variables
//

// Variant A
//
//    00000000001111111111222222222233333333334444444444555555555566666666667777777777
// \x 01234567890123456789012345678901234567890123456789012345678901234567890123456789
// y  ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
// 0  ╔═[ GPIO ]═════════════════════════════════════════════════════════════════════╗
// 1  ║                                                                   │ LEGEND   ║
// 2  ║ PA  0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15 │          ║
// 3  ║    16  17  18  19  20  21  22  23  24  25  26  27  28  29         │     0 1  ║
// 4  ║ PB  0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15 │          ║
// 5  ║    16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31 │  IN ∙ ∙  ║
// 6  ║ PC  0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15 │          ║
// 7  ║    16  17  18  19  20  21  22  23  24  25  26  27  28  29  30     │ OUT ∙ ∙  ║
// 8  ║ PD  0   1   2   3   4   5   6   7   8   9  10                     │          ║
// 9  ╚══════════════════════════════════════════════════════════════════════════════╝
//    ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
//
//
// Variant B
//
//    00000000001111111111222222222233333333334444444444555555555566666666667777777777
// \x 01234567890123456789012345678901234567890123456789012345678901234567890123456789
// y  ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
//  0 ╔═[ GPIO ]═════════════════════════════════════════════════════════════════════╗
//  1 ║   GND 52  50  48  46  44  42  40  38  36  34  32  30  28  26  24  22  +5V    ║
//  2 ║ ┌──┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼─┐   ║
//  3 ║ │  o   o   o   o   o   o   o   o   o   o   o   o   o   o   o   o   o   o │   ║
//  4 ║ │                                                                        │   ║
//  5 ║ │  o   o   o   o   o   o   o   o   o   o   o   o   o   o   o   o   o   o │   ║
//  6 ║ └──┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼─┘   ║
//  7 ║   GND 53  51  49  47  45  43  41  39  37  35  33  31  29  27  25  23  +5V    ║
//  8 ║                                                                              ║
//  9 ║   SCL SDA ARF GND 13  12  11  10   9   8     7   6   5   4   3   2   1   0   ║
// 10 ║ ┌──┼───┼───┼───┼───┼───┼───┼───┼───┼───┼─┐ ┌─┼───┼───┼───┼───┼───┼───┼───┼─┐ ║
// 11 ║ │  o   o   o   o   o   o   o   o   o   o │ │ o   o   o   o   o   o   o   o │ ║
// 12 ║ └────────────────────────────────────────┘ └───────────────────────────────┘ ║
// 13 ║                                                                              ║
// 14 ║   TX3 RX3 TX2 RX2 TX1 RX1 SDA SCL                                            ║
// 15 ║ ┌──┼───┼───┼───┼───┼───┼───┼───┼──┐                                          ║
// 16 ║ │  o   o   o   o   o   o   o   o  │                                          ║
// 17 ║ └─────────────────────────────────┘                                          ║
// 18 ║                                                                CAN CAN       ║
// 19 ║ ┌─────────────────────────────────┐ ┌─────────────────────────────────┐      ║
// 20 ║ │  o   o   o   o   o   o   o   o  │ │  o   o   o   o   o   o   o   o  │      ║
// 21 ║ └──┼───┼───┼───┼───┼───┼───┼───┼──┘ └──┼───┼───┼───┼───┼───┼───┼───┼──┘      ║
// 22 ║   A0  A1  A2  A3  A4  A5  A6  A7      A8  A9  A10 A11 DAC0DAC1 RX  TX        ║
// 23 ╚══════════════════════════════════════════════════════════════════════════════╝
//    ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒

struct GPIO_PIN
{
	char *label;
	char *description;
	PinDescription *g_APinDescription;
}
gpio_pins[] =
{
	{ "0", "PORTA:0; CANTX0", &g_APinDescription[0] }
};

// #############################################################################
// functions
//

int gpio_def_wnd_proc( struct WINDOW_CLASS *window, enum WINDOW_MESSAGE command, int uParam, int vParam )
{
	struct GPIO_CLASS *gpio = (struct GPIO_CLASS *) window->user_def;
	
	switch( command )
	{
		case WM_CREATE:
		{
	
			struct WINDOW_ATTRIBUTES entry_attributes =
			{
				.fg_color = VT100_COLOR_DEFAULT,
				.bg_color = VT100_COLOR_RED,
				.border_style = WINDOW_BORDER_NONE
			};
			
			struct WINDOW_RECT entry_rect =
			{
				.x = 5, .y = 5,
				.w = 21, .h = 1
			};
			
			struct ENTRY_CLASS *entry_class = (struct ENTRY_CLASS *) malloc( sizeof(struct ENTRY_CLASS) );
			memset( entry_class, 0, sizeof(struct ENTRY_CLASS) );
			entry_class->label_width = 12;
			entry_class->label_align = ENTRY_LABEL_LEFT;

			struct WINDOW_CLASS *entry;
			/*entry = window_create(
				window->ushell,
				window,
				"label:",
				&entry_attributes,
				&entry_rect,
				entry_def_wnd_proc,
				entry_class
			);
			
			entry_set_text( entry, "test" );*/

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

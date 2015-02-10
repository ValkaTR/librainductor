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
//
// Variant C
//     00000000001111111111222222222233333333334444444444555555555566666666667777777777
// y/x 01234567890123456789012345678901234567890123456789012345678901234567890123456789
//    ╔══[ GPIO ]════════════════════════════════════════════════════════════════════╗
// 0  ║ 22: PB26    32: PD10    42: PA19    52: PB21                       │LEGEND   ║
// 1  ║ 23: PA14    33: PC1     43: PA20    53: PB14PA               [    33013.5 ]  ║
// 2  ║ 24: PA15    34: PC2     44: PC19                                   │    0 1  ║
// 3  ║ 25: PD0     35: PC3     45: PC18PB                                 │         ║
// 4  ║ 26: PD1     36: PC4     46: PC17                                   │ IN ∙ ∙  ║
// 5  ║ 27: PD2     37: PC5     47: PC16PC                                 │         ║
// 6  ║ 28: PD3     38: PC6     48: PC15                                   │OUT ∙ ∙  ║
// 7  ║ 29: PD6     39: PC7     49: PC14PD                                 │         ║
// 8  ║ 30: PD9     40: PC8     50: PC13                                   │         ║
// 9  ║ 31: PA7     41: PC9     51: PC12                                   │         ║
//    ╚══════════════════════════════════════════════════════════════════════════════╝

struct GPIO_PIN
{
	int id;
	char *name;
	int x;
	int y;
	PinDescription *g_APinDescription;
}
gpio_pins[] =
{
	{ 22, "[22: PB26]", 1, 0, &g_APinDescription[22] },
	{ 23, "[23: PA14]", 1, 1, &g_APinDescription[23] },
	{ 24, "[24: PA15]", 1, 2, &g_APinDescription[24] },
	{ 25, "[25: PD0]", 1, 3, &g_APinDescription[25] },
	{ 26, "[26: PD1]", 1, 4, &g_APinDescription[26] },
	{ 27, "[27: PD2]", 1, 5, &g_APinDescription[27] },
	{ 28, "[28: PD3]", 1, 6, &g_APinDescription[28] },
	{ 29, "[29: PD6]", 1, 7, &g_APinDescription[29] },
	{ 30, "[30: PD9]", 1, 8, &g_APinDescription[30] },
	{ 31, "[31: PA7]", 1, 9, &g_APinDescription[31] },
	
	{ 32, "[32: PD10]", 13, 0, &g_APinDescription[32] },
	{ 33, "[33: PC1]", 13, 1, &g_APinDescription[33] },
	{ 34, "[34: PC2]", 13, 2, &g_APinDescription[34] },
	{ 35, "[35: PC3]", 13, 3, &g_APinDescription[35] },
	{ 36, "[36: PC4]", 13, 4, &g_APinDescription[36] },
	{ 37, "[37: PC5]", 13, 5, &g_APinDescription[37] },
	{ 38, "[38: PC6]", 13, 6, &g_APinDescription[38] },
	{ 39, "[39: PC7]", 13, 7, &g_APinDescription[39] },
	{ 40, "[40: PC8]", 13, 8, &g_APinDescription[40] },
	{ 41, "[41: PC9]", 13, 9, &g_APinDescription[41] },
	
	{ 42, "[42: PA19]", 25, 0, &g_APinDescription[42] },
	{ 43, "[43: PA20]", 25, 1, &g_APinDescription[43] },
	{ 44, "[44: PC19]", 25, 2, &g_APinDescription[44] },
	{ 45, "[45: PC18PB]", 25, 3, &g_APinDescription[45] },
	{ 46, "[46: PC17]", 25, 4, &g_APinDescription[46] },
	{ 47, "[47: PC16PC]", 25, 5, &g_APinDescription[47] },
	{ 48, "[48: PC15]", 25, 6, &g_APinDescription[48] },
	{ 49, "[49: PC14PD]", 25, 7, &g_APinDescription[49] },
	{ 50, "[50: PC13]", 25, 8, &g_APinDescription[50] },
	{ 51, "[51: PC12]", 25, 9, &g_APinDescription[51] },

	{ 52, "[52: PB21]", 37, 8, &g_APinDescription[52] },
	{ 53, "[53: PB14PA]", 37, 9, &g_APinDescription[53] }
};

// #############################################################################
// functions
//

struct WINDOW_CLASS *gpio_create( struct USHELL_CLASS *ushell, int x, int y, int w, int h )
{
	struct WINDOW_ATTRIBUTES window_attributes =
	{
		.fg_color = VT100_COLOR_DEFAULT,
		.bg_color = VT100_COLOR_DEFAULT,
		.border_style = WINDOW_BORDER_DOUBLE
	};
	
	struct WINDOW_RECT window_rect =
	{
		.x = x, .y = y,
		.w = w, .h = h
	};
	
	struct GPIO_CLASS *window_class = malloc( sizeof(struct GPIO_CLASS) );
	memset( window_class, 0, sizeof(struct GPIO_CLASS) );

	struct WINDOW_CLASS *window = window_create(
		ushell,
		NULL,
		"GPIO",
		&window_attributes,
		&window_rect,
		window_class
	);
	
	//window->create_proc = gpio_create_proc;
	//window->destroy_proc = gpio_destroy_proc;
	window->paint_proc = gpio_paint_proc;
	//window->key_event_proc = gpio_key_event_proc;
	//window->character_proc = gpio_character_proc;

	ushell_register_window( ushell, window );
	
	return window;
}

// #############################################################################

bool gpio_create_proc ( struct WINDOW_CLASS *window, struct WINDOW_GENERIC_MESSAGE *msg, void *user_def )
{
	return true;
}

// #############################################################################

bool gpio_paint_proc( struct WINDOW_CLASS *window, struct WINDOW_PAINT_MESSAGE *msg, void *user_def )
{
	for( int j = 1; j < window->rect.h - 1; j++ )
	for( int i = 1; i < window->rect.w - 1; i++ )
	window_write_text_full( window, i, j, false, false, VT100_COLOR_DEFAULT, VT100_COLOR_DEFAULT, " ", -1 );
	
	for( int j = 0; j < 10; j++ )
	window_write_cell_full( window, 68, j, false, false, VT100_COLOR_DEFAULT, VT100_COLOR_DEFAULT, 0xB3 );
	
	window_write_text_full( window, 1, 1, false, false, VT100_COLOR_DEFAULT, VT100_COLOR_DEFAULT, "PA", -1 );
	window_write_text_full( window, 1, 3, false, false, VT100_COLOR_DEFAULT, VT100_COLOR_DEFAULT, "PB", -1 );
	window_write_text_full( window, 1, 5, false, false, VT100_COLOR_DEFAULT, VT100_COLOR_DEFAULT, "PC", -1 );
	window_write_text_full( window, 1, 7, false, false, VT100_COLOR_DEFAULT, VT100_COLOR_DEFAULT, "PD", -1 );
	
	window_write_text_full( window, 69, 0, false, false, VT100_COLOR_DEFAULT, VT100_COLOR_DEFAULT, "LEGEND", -1 );
	window_write_cell_full( window, 73, 2, false, false, VT100_COLOR_DEFAULT, VT100_COLOR_DEFAULT, '0' );
	window_write_cell_full( window, 75, 2, false, false, VT100_COLOR_DEFAULT, VT100_COLOR_DEFAULT, '1' );
	window_write_text_full( window, 70, 4, false, false, VT100_COLOR_DEFAULT, VT100_COLOR_DEFAULT, "IN", -1 );
	window_write_cell_full( window, 73, 4, false, false, VT100_COLOR_BLACK, VT100_COLOR_BLUE, 0xF9 );
	window_write_cell_full( window, 75, 4, false, false, VT100_COLOR_WHITE, VT100_COLOR_BLUE, 0xF9 );
	window_write_text_full( window, 69, 6, false, false, VT100_COLOR_DEFAULT, VT100_COLOR_DEFAULT, "OUT", -1 );
	window_write_cell_full( window, 73, 6, false, false, VT100_COLOR_BLACK, VT100_COLOR_RED, 0xF9 );
	window_write_cell_full( window, 75, 6, false, false, VT100_COLOR_WHITE, VT100_COLOR_RED, 0xF9 );

	for( int i = 0; i < sizeof(gpio_pins) / sizeof(struct GPIO_PIN); i++ )
	{
		int fg_color = VT100_COLOR_DEFAULT;
		int bg_color = VT100_COLOR_DEFAULT;

		//	0 - output
		//	1 - input
		int data_status = PIO_GetOutputDataStatus( gpio_pins[i].g_APinDescription->pPort, gpio_pins[i].g_APinDescription->ulPin );
		int pio_status = PIO_Get( gpio_pins[i].g_APinDescription->pPort, PIO_INPUT, gpio_pins[i].g_APinDescription->ulPin );
		
		bg_color = (data_status == 0 ? VT100_COLOR_RED : VT100_COLOR_BLUE );
		fg_color = (pio_status == 0 ? VT100_COLOR_WHITE : VT100_COLOR_BLACK );

		window_write_text_full( window, gpio_pins[i].x, gpio_pins[i].y, false, false, fg_color, bg_color, gpio_pins[i].name, -1 );
	}

	return true;
}

// #############################################################################

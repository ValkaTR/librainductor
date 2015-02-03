// ############################################################################

/*
 *
 * LibraInductor
 *
 * Created 17 Januar 2015
 * by ValkaTR
 *
 * Compile & flash:
 * 
 *      $ make all && make flash
 * 
 *      'make clean' is required when header file content change
 * 
 * Usage:
 * 
 *      $ screen /dev/ttyACM0 115200
 * 
 * Debug:
 * 
 *      $ dd if=/dev/ttyACM0 bs=1 count=20 | hexdump -C
 *
 */

// ############################################################################

#include "uShell.h"

#include "Window.h"
#include "Window_Prompt.h"
#include "Window_GPIO.h"

#include "garray.h"

void cmd_func_help( struct WINDOW_CLASS *win, GSList *token_list );
void cmd_func_test( struct WINDOW_CLASS *win, GSList *token_list );
void cmd_func_led( struct WINDOW_CLASS *win, GSList *token_list );

struct PROMPT_COMMAND command_list[] =
{
	{ "help", cmd_func_help },
	{ "test", cmd_func_test },
	{ "led", cmd_func_led },
	{ NULL, NULL }
};

struct USHELL_CLASS *ushell;
struct WINDOW_CLASS *prompt;
struct WINDOW_CLASS *gpio;

int ledPin = 13;      // select the pin for the LED

// ############################################################################

void printEvent( char *str, void *userdef );

// ############################################################################

void setup( )
{
	// initialize serial:
	Serial.begin( 115200 );

	//
	// uShell
	//

	ushell = ushell_init( printEvent, NULL );

	//
	// GPIO window
	//
	
	struct WINDOW_ATTRIBUTES gpio_attributes =
	{
		.fg_color = VT100_COLOR_DEFAULT,
		.bg_color = VT100_COLOR_DEFAULT,
		.border_style = WINDOW_BORDER_SINGLE
	};
	
	struct WINDOW_RECT gpio_rect =
	{
		.x = 0, .y = 0,
		.w = 80, .h = 12
	};
	
	struct GPIO_CLASS *gpio_class = (struct GPIO_CLASS *) malloc( sizeof(struct GPIO_CLASS) );
	memset( gpio_class, 0, sizeof(struct GPIO_CLASS) );

	gpio = window_create( 
		NULL,
		"GPIO",
		&gpio_attributes,
		&gpio_rect,
		gpio_def_wnd_proc,
		gpio_class
	);

	//
	// Prompt window
	//
	
	struct WINDOW_ATTRIBUTES prompt_attributes =
	{
		.fg_color = VT100_COLOR_DEFAULT,
		.bg_color = VT100_COLOR_DEFAULT,
		.border_style = WINDOW_BORDER_SINGLE
	};
	
	struct WINDOW_RECT prompt_rect =
	{
		.x = 0, .y = 12,
		.w = 80, .h = 12
	};
	
	struct PROMPT_CLASS *prompt_class = (struct PROMPT_CLASS *) malloc( sizeof(struct PROMPT_CLASS) );
	memset( prompt_class, 0, sizeof(struct PROMPT_CLASS) );
	prompt_class->command_list = command_list;
	prompt_class->prompt = "librainductor> ";

	prompt = window_create( 
		NULL,
		"Prompt",
		&prompt_attributes,
		&prompt_rect,
		prompt_def_wnd_proc,
		prompt_class
	);
	
	//
	
	// declare the ledPin as an OUTPUT:
	pinMode( ledPin, OUTPUT );
}

// ############################################################################

unsigned long timer1 = 0;

void loop( )
{
	/*if( timer1 + 100 < millis( ) )
	{
		timer1 = millis( );
		GString *str_tmp = g_string_sized_new( 32 );
		g_string_printf( str_tmp, "[ %10.1f ]", (float) (timer1 / 1000.0) );
		console_print( ushell->console, 63, 2, false, false, 7, 1, str_tmp->str );
		console_swap_buffers( ushell->console );
		g_string_free( str_tmp, true );
	}*/

	ushell_proccess_loop( ushell );
}

// ############################################################################

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent( )
{
	while( Serial.available( ) )
	{
		// get the new byte:
		char ch = (char) Serial.read( );

		//Serial.print( "[ serialEvent: " );
		//Serial.print( (unsigned int) ch );
		//Serial.print( "]" );

		ushell_proccess_event( ushell, ch );
	}
}

void printEvent( char *str, void *user_def )
{
	Serial.print( str );
}

// ############################################################################
// ############################################################################
// ############################################################################

void cmd_func_help( struct WINDOW_CLASS *win, GSList *token_list )
{
	prompt_print( prompt, "Available commands:" );
	prompt_print( prompt, " " );
	prompt_print( prompt, "help    test" );
	prompt_print( prompt, " " );
}

void cmd_func_test( struct WINDOW_CLASS *win, GSList *token_list )
{
	prompt_print( prompt, "Hello! Love is the solution for everything <3" );
}

void cmd_func_led( struct WINDOW_CLASS *win, GSList *token_list )
{
	GSList *token = token_list->next;
	if( token == NULL )
	{
led_usage:
		prompt_print( prompt, "Change the state of on-board LED" );
		prompt_print( prompt, "Usage: led [on/off]" );
		return;
	}
	
	char *parameter = token->data;
	if( strcmp( parameter, "on" ) == 0 )
		digitalWrite( ledPin, HIGH );
	else if( strcmp( parameter, "off" ) == 0 )
		digitalWrite( ledPin, LOW );
	else
		goto led_usage;
}

// ############################################################################

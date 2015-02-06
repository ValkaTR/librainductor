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
#include "Window_Manager.h"

#include "CyclicStack.h"
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
struct WINDOW_CLASS *window_manager;

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
	// Window Manager
	//
	
	struct WINDOW_ATTRIBUTES window_manager_attributes =
	{
		.fg_color = VT100_COLOR_DEFAULT,
		.bg_color = VT100_COLOR_DEFAULT,
		.border_style = WINDOW_BORDER_SINGLE
	};
	
	struct WINDOW_RECT window_manager_rect =
	{
		.x = 0, .y = 0,
		.w = 80, .h = 24
	};
	
	struct WINDOW_CLASS *window_manager_class = malloc( sizeof(struct WINDOW_MANAGER_CLASS) );
	memset( window_manager_class, 0, sizeof(struct WINDOW_MANAGER_CLASS) );

	window_manager_class = window_create(
		ushell,
		NULL,
		"Window Manager",
		&window_manager_attributes,
		&window_manager_rect,
		window_manager_def_wnd_proc,
		window_manager_class
	);

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
		.x = 1, .y = 1,
		.w = 78, .h = 10
	};
	
	struct GPIO_CLASS *gpio_class = malloc( sizeof(struct GPIO_CLASS) );
	memset( gpio_class, 0, sizeof(struct GPIO_CLASS) );

	gpio = window_create(
		ushell,
		window_manager_class,
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
		.border_style = WINDOW_BORDER_DOUBLE
	};
	
	struct WINDOW_RECT prompt_rect =
	{
		.x = 1, .y = 13,
		.w = 70, .h = 9
	};
	
	struct PROMPT_CLASS *prompt_class = malloc( sizeof(struct PROMPT_CLASS) );
	memset( prompt_class, 0, sizeof(struct PROMPT_CLASS) );
	prompt_class->command_list = command_list;
	prompt_class->prompt = "librainductor> ";

	prompt = window_create(
		ushell,
		window_manager_class,
		"Prompt",
		&prompt_attributes,
		&prompt_rect,
		prompt_def_wnd_proc,
		prompt_class
	);
	
	// declare the ledPin as an OUTPUT:
	pinMode( ledPin, OUTPUT );
}

// ############################################################################

void loop( )
{
	ushell_proccess_loop( ushell, millis( ), -3 );

	struct WINDOW_MESSAGE msg;
	bool msg_result = ushell_get_message( ushell, &msg );
	if( msg_result == true )
	{
		ushell_dispatch_message( ushell, &msg );
	}
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

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
#include "Window_Prompt.h"
#include "Window_GPIO.h"
//#include "Window_Manager.h"

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

	ushell = ushell_init( printEvent, NULL );
	prompt = prompt_create( ushell, command_list, 1, 13, 70, 9 );
	gpio = gpio_create( ushell, 1, 1, 78, 10 );

	Serial.print( sizeof(struct WINDOW_PAINT_MESSAGE) ); Serial.print( " " );
	Serial.print( sizeof(struct WINDOW_KEY_EVENT_MESSAGE) ); Serial.print( " " );
	Serial.print( sizeof(struct WINDOW_CHARACTER_MESSAGE) ); Serial.print( " " );
	Serial.print( sizeof(struct WINDOW_SERIAL_EVENT_MESSAGE) ); Serial.print( " " );
	Serial.print( sizeof(struct WINDOW_GENERIC_MESSAGE) );

	// declare the ledPin as an OUTPUT:
	pinMode( ledPin, OUTPUT );
}

// ############################################################################

void loop( )
{
	ushell_proccess_loop( ushell, millis( ), -3 );

	struct WINDOW_GENERIC_MESSAGE msg;
	bool msg_result = ushell_get_message( ushell, &msg );
	if( msg_result == true )
	{
		//debug_print2( "dispatch_message", (int) msg.window, msg.command );
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

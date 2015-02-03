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

#include "Prompt.h"
#include "Window.h"

#include "garray.h"

void cmd_func_help( char *txt );
void cmd_func_test( char *txt );

struct PROMPT_COMMAND cmd_list[] =
{
	{ "help", cmd_func_help },
	{ "test", cmd_func_test },
	{ NULL, NULL }
};

struct USHELL_CLASS *ushell;

struct WINDOW_CLASS *prompt;

// ############################################################################

void printEvent( char *str, void *userdef );

// ############################################################################

void setup( )
{
	// initialize serial:
	Serial.begin( 115200 );

	ushell = ushell_init( printEvent, NULL );
	
	struct WINDOW_ATTRIBUTES prompt_attributes =
	{
		.fg_color = 7,
		.bg_color = 0,
		.border_style = WINDOW_BORDER_SINGLE
	};
	
	struct WINDOW_RECT prompt_rect =
	{
		.x = 2, .y = 12,
		.w = 77, .h = 10
	};
	
	struct PROMPT_CLASS *prompt_class = (struct PROMPT_CLASS *) malloc( sizeof(struct PROMPT_CLASS) );
	memset( prompt_class, 0, sizeof(struct PROMPT_CLASS) );
	prompt_class->cmd_list = cmd_list;
	prompt_class->prompt = "librainductor> ";

	prompt = window_create( 
		ushell,
		"Prompt",
		&prompt_attributes,
		&prompt_rect,
		prompt_def_wnd_proc,
		prompt_class
	);
	
	// initialize digital pin 13 as an output.
	pinMode(13, OUTPUT);
	
	digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
	delay(250);              // wait for a second
	digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
	delay(250);   

	//Serial.println(prompt->input_line->str);
	//digitalWrite(13, HIGH);delay(250);digitalWrite(13, LOW);delay(250);		

	//Serial.print("love is the solution for everything?\r\n\r\n");
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

void cmd_func_help( char *txt )
{
	prompt_print( prompt, "Available commands:" );
	prompt_print( prompt, " " );
	prompt_print( prompt, "help    test" );
	prompt_print( prompt, " " );
}

void cmd_func_test( char *txt )
{
	prompt_print( prompt, "Hello! Love is the solution for everything <3" );
}

// ############################################################################

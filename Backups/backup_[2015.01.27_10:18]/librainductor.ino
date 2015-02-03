// ############################################################################

/*
 *
 * LibraInductor
 *
 * Created 17 Januar 2015
 * by ValkaTR
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

void cmd_func_help( char *txt );
void cmd_func_test( char *txt );

struct CONSOLE_COMMAND cmd_list[] =
{
	{ "help", cmd_func_help },
	{ "test", cmd_func_test },
	{ NULL, NULL }
};

struct USHELL *ushell;

// ############################################################################

void printEvent( char *str, void *userdef );

// ############################################################################


void setup( )
{
	// initialize serial:
	Serial.begin( 115200 );

	struct USHELL *ushell = ushell_init(
		"librainductor> ",
		cmd_list,
		( void (*) ( char *str, void *user_def ) ) &printEvent,
		NULL
	);
Serial.println( String("cmd_escape_len10: ") + (int) ushell->cmd_escape_len );
	//Serial.print( "\x1B[5;4fsaddsafsdfsdf" );
	//Serial.print( "\x1B[10;10f32345245245624" );
	//Serial.print( "\x1B[6;2fybcxvvcxvxcbb" );
	//Serial.print( "--------------\r\n" );
}

// ############################################################################

void loop( )
{
	Serial.println( String("cmd_escape_len33: ") + (int) ushell->cmd_escape_len );
	ushell->cmd_escape_len = 33;
	Serial.println( String("cmd_escape_len34: ") + (int) ushell->cmd_escape_len );
	delay( 1000 );
	
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
	//Serial.print( "| event: " );
Serial.println( String("cmd_escape_len11: ") + (int) ushell->cmd_escape_len );
	while( Serial.available( ) )
	{
		// get the new byte:
		char ch = (char) Serial.read( );
Serial.println( String("cmd_escape_len12: ") + (int) ushell->cmd_escape_len );
		//Serial.print( (unsigned int) ch );

		ushell_proccess_event( ushell, ch );Serial.println( String("cmd_escape_len13: ") + (int) ushell->cmd_escape_len );
	}
}

void printEvent( char *str, void *user_def )
{Serial.println( String("cmd_escape_len14: ") + (int) ushell->cmd_escape_len );
	Serial.print( str );
}

// ############################################################################
// ############################################################################
// ############################################################################

void cmd_func_help( char *txt )
{
	Serial.print(
		"Available commands:\r\n"
		"\r\n"
		"help    test\r\n"
		"\r\n"
	);
}

void cmd_func_test( char *txt )
{
	//p( "txt: %s;\r\n", txt );
	Serial.print( "Hello!\r\n" );
}

// ############################################################################

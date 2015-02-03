// ############################################################################

/*

 Arduino Shell

 Created 6 March 2014
 by Valentin But

 */

// ############################################################################

#include "shell.h"

// ############################################################################


void setup( )
{
	// initialize serial:
	Serial.begin(115200);

	shell_init();
}

// ############################################################################

void loop( )
{
	proccess_cmd( );
}

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
	p( "txt: %s;\r\n", txt );
	Serial.print( "Hello!\r\n" );
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

		proccess_event( ch );
	}
}

// ############################################################################

// #############################################################################
//
//    CYCLIC STACK CONCEPT
//
//   ╔═══════╦═══════════════╗
//   ║ index ║ *pdata_mem    ║
//   ╠═══════╬═══════════════╣       ╮
//   ║   0   ║ aaaa          ║       │
//   ╟───────╫───────────────╢       │
//   ║   1   ║ bbbb          ║       │
//   ╟───────╫───────────────╢       │
//   ║   2   ║ ccccc         ║       │
//   ╟───────╫───────────────╢       │
//   ║   3   ║ ddd           ║ ←─ ╮──│── stack_position = 3
//   ╟───────╫───────────────╢    │  │
//   ║   4   ║ eeeee         ║    ├──│── stack_queue = 3
//   ╟───────╫───────────────╢    │  │
//   ║   5   ║ fff           ║    │  │
//   ╟───────╫───────────────╢    ╯  ├── stack_size = 8
//   ║   6   ║               ║       │
//   ╟───────╫───────────────╢       │
//   ║   7   ║               ║       │
//   ╚═══════╩═══════════════╝       ╯
//            ╰─────┬─────╯
//              data_lenght = 13
//
//
// Copyleft (C) 2015 Valentin But <valkur@gmail.com>
//
// The author disclaims copyright to this source code.  In place of
// a legal notice, here is a blessing:
//
//  · May you do good and not evil.
//  · May you find forgiveness for yourself and forgive others.
//  · May you share freely, never taking more than you give.
//
//
// #############################################################################
// includes of system headers
//

#include <Arduino.h>

// #############################################################################
// includes of local headers
//

#include "CyclicStack.h"

// #############################################################################
// global variables
//

// #############################################################################
// functions

struct CYCLIC_STACK *cyclic_stack_new( int data_lenght, int stack_size )
{
	struct CYCLIC_STACK *cyclic_stack = malloc( sizeof(struct CYCLIC_STACK) );
	cyclic_stack->pdata_mem = malloc( data_lenght * stack_size );
	cyclic_stack->data_lenght = data_lenght;
	
	cyclic_stack->stack_size = stack_size;
	cyclic_stack->stack_position = 0;
	cyclic_stack->stack_queue = 0;
}

// #############################################################################

bool cyclic_stack_push( struct CYCLIC_STACK *cyclic_stack, void *pdata )
{
	int i = cyclic_stack->stack_position + cyclic_stack->stack_queue;
	if( i == 2 * cyclic_stack->stack_size - 1 )
		return false; // Stack is full
	
	i = i % cyclic_stack->stack_size;
	
	memcpy(
		& ((char *)cyclic_stack->pdata_mem) [i * cyclic_stack->data_lenght],
		pdata,
		cyclic_stack->data_lenght
	);
	
	cyclic_stack->stack_queue += 1;
	
	return true;
}

// #############################################################################

bool cyclic_stack_pop( struct CYCLIC_STACK *cyclic_stack, void *pdata_out )
{
	if( cyclic_stack->stack_queue == 0 )
		return false; // Stack is empty
	
	memcpy(
		pdata_out,
		& ((char *) cyclic_stack->pdata_mem) [cyclic_stack->stack_position * cyclic_stack->data_lenght],
		cyclic_stack->data_lenght
	);
	
	cyclic_stack->stack_position = (cyclic_stack->stack_position + 1) % cyclic_stack->stack_size;
	cyclic_stack->stack_queue -= 1;
	
	return true;
}

// #############################################################################

void cyclic_stack_test( void )
{
	struct CYCLIC_STACK *cyclic_stack = cyclic_stack_new( sizeof(int), 8 );
	
	int x;
	
	for( int j = 0; j < 5; j++ )
	{
		Serial.println( "Push" );
		for( int i = 0; i < 3; i++ )
		{
			x = random(0, 100);
			cyclic_stack_push( cyclic_stack, &x );
		}

		Serial.println( "Debug" );
		for( int i = 0; i < 8; i++ )
		{
			x = ((int *) cyclic_stack->pdata_mem)[i];
			Serial.print( "[" );
			Serial.print( i );
			Serial.print( ":");
			Serial.print( x );
			Serial.print( "]" );
		}

		Serial.println( "---" );
		Serial.println( "Pop" );
		int i = 0;
		while( 1 )
		{
			bool result = cyclic_stack_pop( cyclic_stack, &x );
			if( result == false )
				break;
			
			Serial.print( "[" );
			Serial.print( i );
			Serial.print( ":");
			Serial.print( x );
			Serial.print( "]" );
			i++;
		}
		
		Serial.println( " " );
		Serial.print( "=== Repeat " );
		Serial.print( j + 1 );
		Serial.print( "/" );
		Serial.print( 5 );
		Serial.println( " ===" );
	}
}

// #############################################################################

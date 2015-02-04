// #############################################################################
//
//
//
// #############################################################################

#ifndef __cyclic_stack_h__
#define __cyclic_stack_h__

// #############################################################################
// includes of system headers
//

#include <Arduino.h>

// #############################################################################
// includes of local headers
//

#include <Arduino.h>
#include "gcommon.h"

G_BEGIN_DECLS

// #############################################################################
// type and constant definitions
//

// #############################################################################
// class declarations
//

struct CYCLIC_STACK
{
	void *pdata_mem;
	int data_lenght;
	
	int stack_size;
	int stack_position;
	int stack_queue;
};

// #############################################################################
// function declarations
//

struct CYCLIC_STACK *cyclic_stack_new( int data_lenght, int stack_size );
bool cyclic_stack_push( struct CYCLIC_STACK *cyclic_stack, void *pdata );
bool cyclic_stack_pop( struct CYCLIC_STACK *cyclic_stack, void *pdata_out );

void cyclic_stack_test( void );

// #############################################################################

G_END_DECLS

#endif // __cyclic_stack_h__

// #############################################################################



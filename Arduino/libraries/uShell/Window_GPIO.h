// #############################################################################
//
//
//
// #############################################################################

#ifndef __gpio_h__
#define __gpio_h__

// #############################################################################
// includes of system headers
//

#include <Arduino.h>

// #############################################################################
// includes of local headers
//

#include "uShell.h"

G_BEGIN_DECLS

// #############################################################################
// type and constant definitions
//

// #############################################################################
// class declarations
//

struct GPIO_CLASS
{
	int x;
};

// #############################################################################
// function declarations
//

struct WINDOW_CLASS *gpio_create( struct USHELL_CLASS *ushell, int x, int y, int w, int h );

bool gpio_create_proc ( struct WINDOW_CLASS *window, struct WINDOW_GENERIC_MESSAGE *msg, void *user_def );
bool gpio_paint_proc( struct WINDOW_CLASS *window, struct WINDOW_PAINT_MESSAGE *msg, void *user_def );

// #############################################################################

G_END_DECLS

#endif // __gpio_h__

// #############################################################################



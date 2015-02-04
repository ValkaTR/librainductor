// #############################################################################
//
//
//
// #############################################################################

#ifndef __adc_h__
#define __adc_h__

// #############################################################################
// includes of system headers
//

#include <Arduino.h>

// #############################################################################
// includes of local headers
//

#include "Window.h"
#include "gslist.h"
#include "garray.h"

G_BEGIN_DECLS

// #############################################################################
// type and constant definitions
//

// #############################################################################
// class declarations
//

struct ADC_CLASS
{
	int x;
};

// #############################################################################
// function declarations
//

int adc_def_wnd_proc( struct WINDOW_CLASS *window, enum WINDOW_COMMAND command, int uParam, int vParam );

// #############################################################################

G_END_DECLS

#endif // __adc_h__

// #############################################################################



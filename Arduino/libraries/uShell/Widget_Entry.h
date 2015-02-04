// #############################################################################
//
//
//
// #############################################################################

#ifndef __entry_h__
#define __entry_h__

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

enum ENTRY_LABEL_ALIGN
{
	ENTRY_LABEL_NONE = 0,
	ENTRY_LABEL_LEFT,
	ENTRY_LABEL_RIGHT
};

struct ENTRY_CLASS
{
	GString *text;
	
	enum ENTRY_LABEL_ALIGN label_align;
	int label_width;
};

// #############################################################################
// function declarations
//

void entry_set_text( struct WINDOW_CLASS *window, char *text );

int entry_def_wnd_proc( struct WINDOW_CLASS *window, enum WINDOW_COMMAND command, int uParam, int vParam );

// #############################################################################

G_END_DECLS

#endif // __entry_h__

// #############################################################################



#ifndef GRAPHICS_H_
#define GRAPHICS_H_

// Includes
#include <SDL2/SDL.h>
#include <io/error.h>
#include <io/map.h>

// Function declarations
// Initialises the graphics system, window etc
MESSAGE Graphics_Init
(
	const char *		title,
	const unsigned int	width,
	const unsigned int	height
);

// Deinitialises the graphics system
MESSAGE Graphics_Deinit(void);

// Shows an error dialog on the screen
MESSAGE Graphics_ShowErrorDialog
(
	const char *	title,
	const char *	message
);

void Graphics_DrawMap
(
	MAP	*	map
);

#endif
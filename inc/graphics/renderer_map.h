#ifndef GRAPHICS_MAP_H_
#define GRAPHICS_MAP_H_

// Includes
#include <io/map.h>
#include <graphics/graphics.h>
#include <graphics/framebuffer.h>

// Function declarations
void Graphics_DrawMap
(
	FRAMEBUFFER_HANDLE *	handle,
	MAP	*					map
);

#endif
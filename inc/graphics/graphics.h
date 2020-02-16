#ifndef GRAPHICS_GRAPHICS_H_
#define GRAPHICS_GRAPHICS_H_

// Includes
#include <game/data.h>
#include <graphics/framebuffer.h>

// Function declarations
void Graphics_DrawLine
(
	FRAMEBUFFER_HANDLE * 	handle,
	RENDERER_POINT *		start,
	RENDERER_POINT *		end,
	uint32_t				argb
);

#endif
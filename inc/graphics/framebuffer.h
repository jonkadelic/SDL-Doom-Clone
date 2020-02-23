#ifndef FRAMEBUFFER_H_
#define FRAMEBUFFER_H_

// Includes
#include <io/error.h>
#include <game/data.h>
#include <stdint.h>

// Defines
#define FRAMEBUFFER_WIDTH	(1280)
#define FRAMEBUFFER_HEIGHT	(1024)

// Typedefs
struct framebuffer_handle;
typedef struct framebuffer_handle FRAMEBUFFER_HANDLE;

// Function declarations
MESSAGE Framebuffer_Create
(
	FRAMEBUFFER_HANDLE **	out
);

MESSAGE Framebuffer_Destroy
(
	FRAMEBUFFER_HANDLE *	handle
);

void Framebuffer_Blit
(
	const FRAMEBUFFER_HANDLE *	handle
);

void Framebuffer_Clear
(
	const FRAMEBUFFER_HANDLE *	handle,
	const uint32_t				argb
);

void Framebuffer_SetPixel
(
	const FRAMEBUFFER_HANDLE *	handle,
	const unsigned int			x,
	const unsigned int			y,
	const uint32_t 				argb
);

uint32_t Framebuffer_GetPixel
(
	const FRAMEBUFFER_HANDLE *	handle,
	const unsigned int			x,
	const unsigned int			y
);

int Framebuffer_GetWidth
(
	const FRAMEBUFFER_HANDLE *	handle
);

int Framebuffer_GetHeight
(
	const FRAMEBUFFER_HANDLE *	handle
);

#endif
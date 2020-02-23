#ifndef GRAPHICS_BSP_H_
#define GRAPHICS_BSP_H_

// Includes
#include <io/map.h>

// Function declarations
int BSP_GenerateOrderedLineSet
(
	MAP_POINT *	position,
	NODE *		inputSet,
	NODE **		outputSet
);

#endif
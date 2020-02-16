#ifndef GRAPHICS_BSP_H_
#define GRAPHICS_BSP_H_

// Includes
#include <io/map.h>

// Function declarations
void BSP_GenerateOrderedLineSet
(
	MAP_POINT *	position,
	NODE *		inputSet,
	MAP_WALL *	outputSet
);

#endif
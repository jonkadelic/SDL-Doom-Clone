#ifndef GRAPHICS_BSP_H_
#define GRAPHICS_BSP_H_

// Includes
#include <io/map.h>

// Function declarations
void BSP_GenerateOrderedLineSet
(
	POINT *	position,
	NODE *	inputSet,
	LINE *	outputSet
);

#endif
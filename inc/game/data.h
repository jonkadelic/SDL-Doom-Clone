#ifndef GAME_DATA_H_
#define GAME_DATA_H_

// Includes
#include <stdbool.h>

// Typedefs
typedef struct point
{
	int	x;
	int	y;
} POINT;

typedef struct line
{
	POINT	start;
	POINT	end;
	bool	front;
} LINE;

#endif
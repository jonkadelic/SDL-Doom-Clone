// Includes
#include <graphics/graphics.h>

#include <stdlib.h>

void Graphics_DrawLine
(
	FRAMEBUFFER_HANDLE * 	handle,
	RENDERER_POINT *		start,
	RENDERER_POINT *		end,
	uint32_t				argb
)
{
	int x0 = start->x;
	int y0 = start->y;
	int x1 = end->x;
	int y1 = end->y;

	int dx = abs(x1 - x0);
	int sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0);
	int sy = y0 < y1 ? 1 : -1;
	int err = dx + dy;
	
	while (true)
	{
		int e2 = 2 * err;

		Framebuffer_Plot(handle, x0, y0, argb);
		if (x0 == x1 && y0 == y1)
		{
			break;
		}

		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}
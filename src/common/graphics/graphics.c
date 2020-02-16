// Includes
#include <graphics/graphics.h>

#include <stdlib.h>

// TEMPORARY
#include <unistd.h>

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

		Framebuffer_SetPixel(handle, x0, y0, argb);
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

void Graphics_DrawFilledPolygon
(
	FRAMEBUFFER_HANDLE *	handle,
	RENDERER_POLYGON *		polygon,
	uint32_t				argb
)
{
	bool inShape = false;
	RENDERER_POINT topLeft = polygon->points[0];
	RENDERER_POINT bottomRight = polygon->points[0];
	int i;
	int x, y;

	for (i = 0; i < polygon->count; i++)
	{
		RENDERER_POINT current = polygon->points[i];
		if (current.x < topLeft.x)
		{
			topLeft.x = current.x;
		}
		if (current.y < topLeft.y)
		{
			topLeft.y = current.y;
		}
		if (current.x > bottomRight.x)
		{
			bottomRight.x = current.x;
		}
		if (current.y > bottomRight.y)
		{
			bottomRight.y = current.y;
		}
	}

	for (i = 1; i < polygon->count; i++)
	{
		Graphics_DrawLine(handle, &(polygon->points[i - 1]), &(polygon->points[i]), argb);
	}
	Graphics_DrawLine(handle, &(polygon->points[polygon->count - 1]), &(polygon->points[0]), argb);

	for (y = topLeft.y; y <= bottomRight.y; y++)
	{
		inShape = false;
		for (x = topLeft.x; x <= bottomRight.x; x++)
		{
			uint32_t currentPixel = Framebuffer_GetPixel(handle, x, y);
			uint32_t nextPixel = Framebuffer_GetPixel(handle, x + 1, y);
			if (currentPixel == argb && nextPixel != argb)
			{
				inShape = !inShape;
			}
			if (inShape)
			{
				Framebuffer_SetPixel(handle, x, y, argb);
			}
		}
	}
}
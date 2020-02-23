// Includes
#include <graphics/graphics.h>

#include <stdlib.h>

// Typedefs
typedef struct line_data
{
	RENDERER_POINT current;
	int dx;
	int sx;
	int dy;
	int sy;
	int err;
	int e2;
} LINE_DATA;

// Function definitions
void Graphics_DrawLine
(
	FRAMEBUFFER_HANDLE * 	handle,
	RENDERER_POINT *		start,
	RENDERER_POINT *		end,
	uint32_t				argb
)
{
	LINE_DATA data =
	{
		.current = { start->x, start->y },
		.dx = abs(end->x - start->x),
		.sx = start->x < end->x ? 1 : -1,
		.dy = -abs(end->y - start->y),
		.sy = start->y < end->y ? 1 : -1
	};
	data.err = data.dx + data.dy;
	
	while (true)
	{
		data.e2 = data.err * 2;

		Framebuffer_SetPixel(handle, data.current.x, data.current.y, argb);
		if (data.current.x == end->x && data.current.y == end->y)
		{
			break;
		}

		if (data.e2 >= data.dy)
		{
			data.err += data.dy;
			data.current.x += data.sx;
		}
		if (data.e2 <= data.dx)
		{
			data.err += data.dx;
			data.current.y += data.sy;
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

void Graphics_DrawWall
(
	FRAMEBUFFER_HANDLE *	handle,
	int						aX,
	int						aY1,
	int						aY2,
	int						bX,
	int						bY1,
	int						bY2,
	uint32_t				argb
)
{
	RENDERER_POINT topLeft, topRight, bottomLeft, bottomRight;
	int x, y;
	LINE_DATA topLine, bottomLine;

	if (aX < bX)
	{
		topLeft.x = bottomLeft.x = aX;
		topRight.x = bottomRight.x = bX;
		if (aY1 < aY2)
		{
			topLeft.y = aY1;
			bottomLeft.y = aY2;
		}
		else
		{
			topLeft.y = aY2;
			bottomLeft.y = aY1;
		}
		if (bY1 < bY2)
		{
			topRight.y = bY1;
			bottomRight.y = bY2;
		}
		else
		{
			topRight.y = bY2;
			bottomRight.y = bY1;
		}
	}
	else
	{
		topLeft.x = bottomLeft.x = bX;
		topRight.x = bottomRight.x = aX;
		if (bY1 < bY2)
		{
			topLeft.y = bY1;
			bottomLeft.y = bY2;
		}
		else
		{
			topLeft.y = bY2;
			bottomLeft.y = bY1;
		}
		if (aY1 < aY2)
		{
			topRight.y = aY1;
			bottomRight.y = aY2;
		}
		else
		{
			topRight.y = aY2;
			bottomRight.y = aY1;
		}
	}
	

	topLine.current = topLeft;
	topLine.dx = abs(topRight.x - topLeft.x);
	topLine.sx = topLeft.x < topRight.x ? 1 : -1;
	topLine.dy = -abs(topRight.y - topLeft.y);
	topLine.sy = topLeft.y < topRight.y ? 1 : -1;
	topLine.err = topLine.dx + topLine.dy;
	bottomLine.current = bottomLeft;
	bottomLine.dx = abs(bottomRight.x - bottomLeft.x);
	bottomLine.sx = bottomLeft.x < bottomRight.x ? 1 : -1;
	bottomLine.dy = -abs(bottomRight.y - bottomLeft.y);
	bottomLine.sy = bottomLeft.y < bottomRight.y ? 1 : -1;
	bottomLine.err = bottomLine.dx + bottomLine.dy;

	for (x = topLeft.x; x <= topRight.x; x++)
	{
		for (y = topLine.current.y; y <= bottomLine.current.y; y++)
		{
			Framebuffer_SetPixel(handle, x, y, argb);
		}
		// Framebuffer_SetPixel(handle, topLine.current.x, topLine.current.y, argb);
		// Framebuffer_SetPixel(handle, bottomLine.current.x, bottomLine.current.y, argb);

		topLine.e2 = topLine.err * 2;

		if (topLine.e2 >= topLine.dy)
		{
			topLine.err += topLine.dy;
			topLine.current.x += topLine.sx;
		}
		if (topLine.e2 <= topLine.dx)
		{
			topLine.err += topLine.dx;
			topLine.current.y += topLine.sy;
		}

		bottomLine.e2 = bottomLine.err * 2;

		if (bottomLine.e2 >= bottomLine.dy)
		{
			bottomLine.err += bottomLine.dy;
			bottomLine.current.x += bottomLine.sx;
		}
		if (bottomLine.e2 <= bottomLine.dx)
		{
			bottomLine.err += bottomLine.dx;
			bottomLine.current.y += bottomLine.sy;
		}
	}
}
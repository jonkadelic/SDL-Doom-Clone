// Includes
#include <graphics/graphics.h>

#include <math.h>

// Global variables
static SDL_Window *		window = NULL;
static SDL_Surface *	surface = NULL;
static SDL_Renderer *	renderer = NULL;
static SDL_Texture *	texture = NULL;

static uint32_t *		framebuffer;

static uint32_t			drawColor;

static int screenWidth = 640;
static int screenHeight = 480;

// Function declarations
void Framebuffer_Plot(int x, int y);

// Function definitions
MESSAGE Graphics_Init
(
	const char *		title,
	const unsigned int	width,
	const unsigned int	height
)
{
    screenWidth = width;
    screenHeight = height;

    // Initialise video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        THROW_ERROR(STATUS_FAILURE, "Could not initialise SDL!");
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        THROW_ERROR(STATUS_FAILURE, "Could not create SDL window!");
    }

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		THROW_ERROR(STATUS_FAILURE, "Could not create SDL renderer!");
	}

    surface = SDL_GetWindowSurface(window);
    if (surface == NULL)
    {
        THROW_ERROR(STATUS_FAILURE, "Could not get SDL window surface!");
    }

	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
	if (texture == NULL)
	{
		THROW_ERROR(STATUS_FAILURE, "Could not create framebuffer texture!");
	}

	framebuffer = malloc(width * height * sizeof(uint32_t));
	if (framebuffer == NULL)
	{
		THROW_ERROR(STATUS_FAILURE, "Could not create framebuffer array!");
	}

	drawColor = 0;
	memset(framebuffer, drawColor, width * height * sizeof(uint32_t));

    RETURN_STATUS_OK;
}

MESSAGE Graphics_Deinit(void)
{
	SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    RETURN_STATUS_OK;
}

MESSAGE Graphics_ShowErrorDialog
(
	const char *	title,
	const char *	message
)
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, message, window);

	RETURN_STATUS_OK;
}

void Graphics_StartFrameRender(void)
{

}

void Graphics_EndFrameRender(void)
{
	SDL_UpdateTexture(texture, NULL, framebuffer, screenWidth * sizeof(uint32_t));

	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void Framebuffer_Plot(int x, int y)
{
	if (x < 0 || x >= screenWidth || y < 0 || y >= screenHeight)
	{
		return;
	}
	framebuffer[(y * screenWidth) + x] = drawColor;
}

void Graphics_SetDrawColor
(
	int r,
	int g,
	int b,
	int a
)
{
	drawColor = ((a & 0xFF) << 24) | ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | ((b & 0xFF) << 0);
}

void Graphics_DrawLine
(
	RENDERER_POINT *	start,
	RENDERER_POINT *	end
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

		Framebuffer_Plot(x0, y0);
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
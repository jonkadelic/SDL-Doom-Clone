// Includes
#include <graphics/graphics.h>

// Global variables
static SDL_Window *		window = NULL;
static SDL_Surface *	surface = NULL;
static SDL_Renderer *	renderer = NULL;

static int screenWidth = 640;
static int screenHeight = 480;

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
	SDL_RenderPresent(renderer);
}

void Graphics_SetDrawColor
(
	int r,
	int g,
	int b,
	int a
)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void Graphics_DrawLine
(
	LINE *	line
)
{
	SDL_RenderDrawLine
	(
		renderer,
		line->start.x,
		line->start.y,
		line->end.x,
		line->end.y
	);
}